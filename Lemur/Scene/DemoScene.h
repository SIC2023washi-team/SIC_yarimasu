#pragma once
#include "BaseScene.h"
#include "Lemur/Component/Stage.h"
#include "../Component/GameObject.h"
#include "../Component/DemoPlayer.h"
#include "../Graphics/shader.h"
#include "../Graphics/texture.h"
#include "../Graphics/framework.h"

// BLOOM
#include "../Graphics/bloom.h"

class DemoScene :public Lemur::Scene::BaseScene
{
public:
    DemoScene() {}
    ~DemoScene() override {};

    // 初期化
    void Initialize()override;

    // 終了化
    void Finalize()override;

    // 更新処理
    void Update(float elapsedTime)override;

    // 描画処理
    void Render(float elapsedTime)override;

    GameObject* CreatePlayer()
    {
        return new GameObject(
            new DemoPlayerInputComponent(),
            new DemoPlayerPhysicsComponent(),
            new DemoPlayerGraphicsComponent()
        );
    }

    GameObject* CreateStage()
    {
        return new GameObject(
            new StageInputComponent(),
            new StagePhysicsComponent(),
            new StageGraphicsComponent()
        );
    }

private:

    std::unique_ptr<framebuffer> framebuffers[8];

    std::unique_ptr<fullscreen_quad> bit_block_transfer;

    // SKYMAP
    std::unique_ptr<fullscreen_quad> bit_block_transfer_sky;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> skymap;


    Microsoft::WRL::ComPtr<ID3D11PixelShader> pixel_shaders[8];
    // BLOOM
    std::unique_ptr<bloom> bloomer;

    // MASK
    struct dissolve_constants {
        DirectX::XMFLOAT4 parameters; // x : ディゾルブ適応量、yzw : 空き
    };
    float dissolve_value{ 0.5f };
    Microsoft::WRL::ComPtr<ID3D11Buffer> dissolve_constant_buffer;

    D3D11_TEXTURE2D_DESC mask_texture2dDesc;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mask_texture;
    std::shared_ptr<sprite> dummy_sprite;
    Microsoft::WRL::ComPtr<ID3D11VertexShader> sprite_vertex_shader;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> sprite_input_layout;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> sprite_pixel_shader;

    //Map
    GameObject* stage;

    //DemoPlayer
    GameObject* player;

    // skkind
    std::shared_ptr<skinned_mesh> skinned_meshes[8];

    // バッファー＝データを一時的に保持するメモリストレージ領域
    // ・プログラム側で定数バッファに値を格納することで
    // 　シェーダー内でプログラム側のパラメータを参照できる
    // ・ワールド行列、ビュー行列、プロジェクション行列などの
    // 　パラメータを定数バッファに書き込むことで、
    // 　シェーダー内で座標変換の計算ができる
    struct scene_constants
    {
        DirectX::XMFLOAT4X4 view_projection; // ビュー・プロジェクション変換行列 
        DirectX::XMFLOAT4 light_direction; // ライトの向き
        DirectX::XMFLOAT4 camera_position; // カメラ位置
		// SKYMAP
        DirectX::XMFLOAT4X4 inv_view_projection;
    };
    Microsoft::WRL::ComPtr<ID3D11Buffer> constant_buffers[8];

    DirectX::XMFLOAT4 camera_position{ 0.0f, 0.0f, -10.0f, 1.0f };
    DirectX::XMFLOAT4 light_direction{ 0.0f, 0.0f, 1.0f, 0.0f };

    DirectX::XMFLOAT3 translation{ 0, 0, 0 };
    DirectX::XMFLOAT3 scaling{ 1, 1, 1 };
    DirectX::XMFLOAT3 rotation{ 0, 0, 0 };
    DirectX::XMFLOAT4 material_color{ 1, 1, 1, 1 };
};