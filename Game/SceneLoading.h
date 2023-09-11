#pragma once
#include"./Lemur/Scene/BaseScene.h"
#include"./Lemur/Scene/SceneManager.h"
#include"./Lemur/Graphics/shader.h"
#include"./Lemur/Graphics/texture.h"
#include"./Lemur/Graphics/framework.h"
#include <thread>

// ローディングシーン
class SceneLoading: public Lemur::Scene::BaseScene
{
public:
    SceneLoading(BaseScene* nextScene) :nextScene(nextScene) {}
    SceneLoading() {}
    ~SceneLoading()override {}

    // 初期化
    void Initialize()override;

    // 終了化
    void Finalize()override;

    // 更新処理
    void Update(HWND hwnd, float elapsedTime)override;

    // 描画処理
    void Render(float elapsedTime)override;

private:
    // ローディングスレッド
    static void LoadingThread(SceneLoading* scene);

private:
    float angle = 0.0f;
    BaseScene* nextScene = nullptr;
    std::thread* thread = nullptr;
};
