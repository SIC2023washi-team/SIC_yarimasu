#include "UI.h"
#include "SceneGame.h"
#include <imgui.h>




void UiInputComponent::Update(GameObject* gameobj, float elapsedTime)
{
}

void UiPhysicsComponent::Initialize(GameObject* gameobj)
{
}

void UiPhysicsComponent::Update(GameObject* gameobj, float elapsedTime)
{
	Mouse& mouse = Input::Instance().GetMouse();
	

}

void UiGraphicsComponent::Initialize(GameObject* gameobj)
{
	Ui* ui = dynamic_cast<Ui*> (gameobj);
	Lemur::Graphics::Graphics& graphics = Lemur::Graphics::Graphics::Instance();
	
	pause = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\pause.png");
	//option[ui->ShopNumber::SpeedUp_A] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\AttackSpeedUp.png");
	//option[ui->ShopNumber::SpeedUp_P] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\SpeedUp.png");
	//option[ui->ShopNumber::Canon] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\Canon.png");
	//option[ui->ShopNumber::Mine] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\mine.png");
	//option[ui->ShopNumber::PowerUp] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\powerUp.png");
	ui->UiTypes = ui->NumDelivery[0];

	switch (ui->UiTypes)
	{
	case 2:
		switch (ui->NumDelivery[2])
		{
		case 0:
			UiBase[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\attack_speed.png");
			break;

		case 1:
			UiBase[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\bullet_velocity.png");
			break;
		case 2:
			UiBase[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\penetration_force.png");
			break;
		case 3:
			UiBase[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\offensive_power.png");
			break;
		}
		UiBase[0] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\UiBase.png");

		break;
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
	switch (ui->UiTypes)
	{
	case 2:
		if (ui->NumDelivery[5] == 1)
		{
			UiBase[0]->render(immediate_context, 300.0f + 250 * ui->NumDelivery[1], 100.0f, 200.0f, 200.0f, 1.5f, 1.5f, 1.5f, 1.0f, (0));
			UiBase[1]->render(immediate_context, 300.0f + 250 * ui->NumDelivery[1], 100.0f, 200.0f, 200.0f, 1.5f, 1.5f, 1.5f, 1.0f, (0));
		}
		break;
	}


}