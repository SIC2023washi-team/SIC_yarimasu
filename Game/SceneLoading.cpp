#include "SceneLoading.h"

void SceneLoading::Initialize()
{
    // �X���b�h�J�n
    thread = new std::thread(LoadingThread, this);
}

void SceneLoading::Finalize()
{
}

void SceneLoading::Update(HWND hwnd, float elapsedTime)
{
    constexpr float speed = 180;
    angle += speed * elapsedTime;

    // ���̃V�[���̏���������������V�[����؂�ւ���
    if (nextScene->IsReady())
    {
        Lemur::Scene::SceneManager::Instance().ChangeScene(nextScene);
        nextScene = nullptr;
    }
}

void SceneLoading::Render(float elapsedTime)
{
}

void SceneLoading::LoadingThread(SceneLoading* scene)
{
    // COM�֘A�̏������ŃX���b�h���ɌĂԕK�v������
    CoInitialize(nullptr);

    // ���̃V�[���̏������s��
    scene->nextScene->Initialize();

    // �X���b�h���I���O��COM�֘A�̏I����
    CoUninitialize();

    // ���̃V�[���̏��������ݒ�
    scene->nextScene->SetReady();
}
