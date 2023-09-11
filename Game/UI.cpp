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
			//çUåÇë¨ìx
			UiBase[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\attack_speed.png");
			break;

		case 1:
			//íeë¨ìx
			UiBase[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\bullet_velocity.png");
			break;
		case 2:
			//ä—í óÕ
			UiBase[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\penetration_force.png");
			break;
		case 3:
			//çUåÇóÕ
			UiBase[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\offensive_power.png");
			break;
		}
		UiBase[0] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\UiBase.png");
		ui->Uisize = { 200.0f,200.0f };
;

		break;
	case 3:
		UiBase[0] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\pause.png");
		break;
	}
	ui->UiColor = { 2.0f,2.0f,2.0f,1.0f };
}

void UiGraphicsComponent::Update(GameObject* gameobj)
{
	Ui* ui = dynamic_cast<Ui*> (gameobj);
	Lemur::Graphics::Graphics& graphics = Lemur::Graphics::Graphics::Instance();
	Mouse& mouse = Input::Instance().GetMouse();

	switch (ui->UiTypes)
	{
	case 2:
		ui->Uiposition.x = 300.0 + 250 * ui->NumDelivery[1];
		ui->Uiposition.y = 130.0f;
		if (ui->NumDelivery[5] == 1)
		{
			if (static_cast<float>(mouse.GetOldPositionX()) < ui->Uiposition.x + ui->Uisize.x
				&& ui->Uiposition.x < static_cast<float>(mouse.GetOldPositionX()))
						//static_cast<float>(mouse.GetOldPositionY());
			{
				ui->UiColor = { 0.5f,0.5f,0.5f,1.0f };
				if (mouse.GetButtonDown() == mouse.BTN_LEFT)
				{
					ui->NumDelivery[6];
					
				}

			}
			else
			{
				ui->UiColor = { 2.0f,2.0f,2.0f,1.0f };
			}
		}
		break;
	}



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
			UiBase[0]->render(immediate_context, ui->Uiposition.x, ui->Uiposition.y, ui->Uisize.x, ui->Uisize.y, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0));
			UiBase[1]->render(immediate_context, ui->Uiposition.x, ui->Uiposition.y, ui->Uisize.x, ui->Uisize.y, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0));
		}
		break;
	case 3:
		if (ui->NumDelivery[5] == 1)
		{
			UiBase[0]->render(immediate_context, 0, 0, 1280.0f, 720.0f, 1.0f, 1.0f, 1.0f, 0.5f, (0),100,100,1920,100);
			
		}
	}


}