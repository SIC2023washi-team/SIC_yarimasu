#include "UI.h"
#include <imgui.h>



void UiInputComponent::Update(GameObject* gameobj, float elapsedTime)
{
}

void UiPhysicsComponent::Initialize(GameObject* gameobj)
{
}

void UiPhysicsComponent::Update(GameObject* gameobj, float elapsedTime)
{
}

void UiGraphicsComponent::Initialize(GameObject* gameobj)
{
	Ui* ui = dynamic_cast<Ui*> (gameobj);
	Lemur::Graphics::Graphics& graphics = Lemur::Graphics::Graphics::Instance();

	pause = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\pause.png");
	option[ui->ShopNumber::SpeedUp_A] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\AttackSpeedUp.png");
	option[ui->ShopNumber::SpeedUp_P] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\SpeedUp.png");
	option[ui->ShopNumber::Canon] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\Canon.png");
	option[ui->ShopNumber::Mine] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\mine.png");
	option[ui->ShopNumber::PowerUp] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\powerUp.png");
	for (int i = 0; i < 5; i++)
	{
		UiBase[i] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\UiBase.png");
	}

}

void UiGraphicsComponent::Update(GameObject* gameobj)
{
}

void UiGraphicsComponent::Render(GameObject* gameobj, float elapsedTime, ID3D11PixelShader* replaced_pixel_shader)
{
	Ui* ui = dynamic_cast<Ui*> (gameobj);
	Lemur::Graphics::Graphics& graphics = Lemur::Graphics::Graphics::Instance();

	ID3D11DeviceContext* immediate_context = graphics.GetDeviceContext();
	option[ui->ShopNumber::SpeedUp_A]->render(immediate_context, 50.0f, 50.0f, 50.0f, 50.0f);
	option[ui->ShopNumber::SpeedUp_P]->render(immediate_context, 50.0f, 50.0f, 50.0f, 50.0f);
	option[ui->ShopNumber::Canon]->render(immediate_context, 50.0f, 50.0f, 50.0f, 50.0f);
	option[ui->ShopNumber::Mine]->render(immediate_context, 50.0f, 50.0f, 50.0f, 50.0f);
	option[ui->ShopNumber::PowerUp]->render(immediate_context, 50.0f, 50.0f, 50.0f, 50.0f);
	if (ui->ShopFlag == true)
	{
		for (int i = 0; i < 5; i++)
		{
			UiBase[i]->render(immediate_context, 50.0f + 250 * i, 50.0f, 200.0f, 200.0f, 1.5f, 1.5f, 1.5f, 1.0f, (0));
		}
	}
}