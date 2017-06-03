//
// Created by sunsijie on 17-6-3.
//

#ifndef GAMEOFLIFE_DIRECTOR_H
#define GAMEOFLIFE_DIRECTOR_H
#include <queue>
#include <pthread.h>
#include <Matrix.h>
#include <semaphore.h>
#include <memory>

class Director
{
private:
    int queueSize, historyLimit;
    std::queue<Matrix::MatrixType> matrixQueue, historyQueue;
    pthread_t thread_id;
    sem_t empty_sem, full_sem;
    pthread_mutex_t mutex;
    std::shared_ptr<Matrix> matrixPtr;
    Matrix::MatrixType cur;

    static void* ProducingThread(void* param)
    {
        Director* mthis = static_cast<Director*>(param);
        while (true)
        {
            pthread_testcancel();
            sem_wait(&mthis->empty_sem);
            pthread_mutex_lock(&mthis->mutex);
            mthis->matrixQueue.push(mthis->matrixPtr->getcurrentMatrix());
            pthread_mutex_unlock(&mthis->mutex);
            sem_post(&mthis->full_sem);
            mthis->matrixPtr->GetNextMatrix();
            pthread_testcancel();
        }
        return nullptr;
    };

    void InitSemas()
    {
        sem_init(&empty_sem, 0, (unsigned int)queueSize);
        sem_init(&full_sem, 0, 0);
        pthread_mutex_init(&mutex, NULL);
    }

public:
    Director(int queueSize, int historyLimit) :queueSize(queueSize), historyLimit(historyLimit)
    {
        InitSemas();
    }

    void StartProducing()
    {
        pthread_mutex_lock(&mutex);
        matrixQueue = std::queue<Matrix::MatrixType>();
        pthread_mutex_unlock(&mutex);
        historyQueue= std::queue<Matrix::MatrixType>();
        InitSemas();
        pthread_create(&thread_id, nullptr, &Director::ProducingThread, this);
    }

    void StopProducing()
    {
        pthread_cancel(thread_id);
    }

    const Matrix::MatrixType* PopCurrentMatrix()
    {
        sem_wait(&full_sem);
        pthread_mutex_lock(&mutex);
        cur.swap(matrixQueue.front());
        matrixQueue.pop();
        pthread_mutex_unlock(&mutex);
        sem_post(&empty_sem);

        historyQueue.push(cur);
        if (historyQueue.size() > (unsigned int)historyLimit)
        {
            historyQueue.pop();
        }

        return &cur;
    }

    void SetMatrix(std::shared_ptr<Matrix> ptr)
    {
        pthread_mutex_lock(&mutex);
        matrixQueue = std::queue<Matrix::MatrixType>();
        pthread_mutex_unlock(&mutex);
        historyQueue= std::queue<Matrix::MatrixType>();
        InitSemas();
        matrixPtr = ptr;
    }
};

#endif //GAMEOFLIFE_DIRECTOR_H
