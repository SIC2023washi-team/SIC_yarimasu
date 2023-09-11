#include "SceneLoading.h"

void SceneLoading::Initialize()
{
    // スレッド開始
    thread = new std::thread(LoadingThread, this);
}

void SceneLoading::Finalize()
{
}

void SceneLoading::Update(HWND hwnd, float elapsedTime)
{
    constexpr float speed = 180;
    angle += speed * elapsedTime;

    // 次のシーンの準備が完了したらシーンを切り替える
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
    // COM関連の初期化でスレッド毎に呼ぶ必要がある
    CoInitialize(nullptr);

    // 次のシーンの初期を行う
    scene->nextScene->Initialize();

    // スレッドが終わる前にCOM関連の終了化
    CoUninitialize();

    // 次のシーンの準備完了設定
    scene->nextScene->SetReady();
}
