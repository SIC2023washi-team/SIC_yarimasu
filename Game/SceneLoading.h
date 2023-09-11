#pragma once
#include"./Lemur/Scene/BaseScene.h"
#include"./Lemur/Scene/SceneManager.h"
#include"./Lemur/Graphics/shader.h"
#include"./Lemur/Graphics/texture.h"
#include"./Lemur/Graphics/framework.h"
#include <thread>

// ���[�f�B���O�V�[��
class SceneLoading: public Lemur::Scene::BaseScene
{
public:
    SceneLoading(BaseScene* nextScene) :nextScene(nextScene) {}
    SceneLoading() {}
    ~SceneLoading()override {}

    // ������
    void Initialize()override;

    // �I����
    void Finalize()override;

    // �X�V����
    void Update(HWND hwnd, float elapsedTime)override;

    // �`�揈��
    void Render(float elapsedTime)override;

private:
    // ���[�f�B���O�X���b�h
    static void LoadingThread(SceneLoading* scene);

private:
    float angle = 0.0f;
    BaseScene* nextScene = nullptr;
    std::thread* thread = nullptr;
};
