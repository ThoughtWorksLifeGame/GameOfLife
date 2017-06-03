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

class Director {
private:
    int queueSize, historyLimit;
    std::queue<Matrix::MatrixType> matrixQueue;
    std::vector<Matrix::MatrixType> historyQueue;
    pthread_t thread_id;
    sem_t empty_sem, full_sem;
    pthread_mutex_t mutex;
    std::shared_ptr<Matrix> matrixPtr;
    Matrix::MatrixType cur;
    bool isThreadRunning = false;

    static void *ProducingThread(void *param);

    void InitSemas();

    void InitQueues();

public:
    Director(int queueSize, int historyLimit);

    void StartProducing();

    void StopProducing();

    const Matrix::MatrixType *PopCurrentMatrix();

    void SetMatrix(std::shared_ptr<Matrix> ptr);

    const Matrix::MatrixType *GetHistory(int index);

    void SetHistoryLimit(int limit);

    size_t GetHistorySize();
};

#endif //GAMEOFLIFE_DIRECTOR_H
