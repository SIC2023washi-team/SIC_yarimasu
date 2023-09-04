#pragma once

#include "BaseScene.h"

// シーンマネージャー
namespace Lemur::Scene
{
    class SceneManager
    {
    private:
        SceneManager() {}
        ~SceneManager() {}

    public:
        // 唯一のインスタンス取得
        static SceneManager& Instance()
        {
            static SceneManager instance;
            return instance;
        }

        // 更新処理
        void Update(float elapsedTime);

        // 描画処理
        void Render(float elapsedTime);

        // シーンクリア
        void Clear();

        // シーンの切り替え
        void ChangeScene(BaseScene* scene);

    private:
        BaseScene* currentScene = nullptr;
        BaseScene* nextScene = nullptr;
    };
}