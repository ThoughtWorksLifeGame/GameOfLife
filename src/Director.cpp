//
// Created by sunsijie on 17-6-3.
//

#include "Director.h"
#include <cassert>

void *Director::ProducingThread(void *param) {
    Director *mthis = static_cast<Director *>(param);
    while (true) {
        pthread_testcancel();

        sem_wait(&mthis->empty_sem);

        pthread_mutex_lock(&mthis->mutex);
        mthis->matrixQueue.push(mthis->matrixPtr->GetCurrentMatrix());
        pthread_mutex_unlock(&mthis->mutex);

        sem_post(&mthis->full_sem);

        mthis->matrixPtr->GetNextMatrix();

        pthread_testcancel();
    }
};

void Director::InitSemas() {
    sem_init(&empty_sem, 0, (unsigned int) queueSize);
    sem_init(&full_sem, 0, 0);
    pthread_mutex_init(&mutex, NULL);
}

Director::Director(int queueSize, int historyLimit) : queueSize(queueSize), historyLimit(historyLimit) {
    InitSemas();
}

void Director::StartProducing() {
    InitSemas();
    InitQueues();
    pthread_create(&thread_id, nullptr, &Director::ProducingThread, this);
    isThreadRunning = true;
}

void Director::StopProducing() {
    pthread_cancel(thread_id);
    isThreadRunning = false;
}

const Matrix::MatrixType *Director::PopCurrentMatrix() {
    sem_wait(&full_sem);
    pthread_mutex_lock(&mutex);
    assert(!matrixQueue.empty());
    cur.swap(matrixQueue.front());
    matrixQueue.pop();
    pthread_mutex_unlock(&mutex);
    sem_post(&empty_sem);

    historyQueue.push_back(cur);
    if (historyQueue.size() > (unsigned int) historyLimit) {
        historyQueue.erase(historyQueue.begin());
    }

    return &cur;
}

void Director::SetMatrix(std::shared_ptr<Matrix> ptr) {
    if (isThreadRunning)
    {
        StopProducing();
    }
    InitQueues();
    historyQueue.clear();
    InitSemas();
    matrixPtr = ptr;
}

void Director::InitQueues() {
    pthread_mutex_lock(&mutex);
    matrixQueue = std::queue<Matrix::MatrixType>();
    pthread_mutex_unlock(&mutex);
}

void Director::SetHistoryLimit(int limit) {
    historyLimit = limit;
}

const Matrix::MatrixType *Director::GetHistory(int index) {
    if ((size_t)index >= historyQueue.size() || index < 0)
    {
        return nullptr;
    }
    else
    {
        return &historyQueue[index];
    }
}

size_t Director::GetHistorySize() {
    return historyQueue.size();
}
