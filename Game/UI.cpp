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
		UiBase[0] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\UiBase.png");
		UiBase[2] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\junk.png");
		UiBase[3] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\font.png");
		ui->Uisize = { 200.0f,200.0f };
		switch (ui->NumDelivery[2])
		{
		case 0:
			//攻撃速度
			UiBase[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\attack_speed.png");
			UiBase[4] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\attckspeedUp.png");
			ui->price = 100;
			break;

		case 1:
			//弾速度
			UiBase[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\bullet_velocity.png");
			UiBase[4] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\SpeedUp.png");
			ui->price = 100;
			break;
		case 2:
			//貫通力
			UiBase[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\penetration_force.png");
			UiBase[4] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\bretHPUp.png");
			ui->price = 100;
			break;
		case 3:
			//攻撃力
			UiBase[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\offensive_power.png");
			UiBase[4] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\powerUp.png");
			ui->price = 100;
			break;
		case 4:
			//HP
			UiBase[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\HP.png");
			UiBase[4] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\HPUp.png");
			ui->price = 100;
			break;
		}

;

		break;
	case 3:
		UiBase[0] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\pause.png");
		break;
	case 4:
		UiBase[0] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\HP_bit.png");
		break;
	case 5:
		UiBase[0] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\return.png");
		ui->Uisize = { 400.0f, 30.0f };
		break;
	case 6:
		UiBase[0] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\junk.png");
		UiBase[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\font.png");
		ui->junkDigits = 1;
		ui->Uiposition2 = { 25,80 };
		ui->Uisize2 = { 20,40 };
		ui->Uiposition = { 45,80 };
		ui->Uisize = { 80,40 };
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
		ui->Uiposition2.x = 300.0 + 250 * ui->NumDelivery[1];
		ui->Uiposition2.y = 150.0f;
		ui->Uiposition3.x = 300.0 + 250 * ui->NumDelivery[1];
		ui->Uiposition3.y = 100.0f;

		ui->Uisize3 = { 30,30 };
		if (ui->NumDelivery[5] == 1)
		{
			if (static_cast<float>(mouse.GetOldPositionX()) < ui->Uiposition.x + ui->Uisize.x
				&& ui->Uiposition.x < static_cast<float>(mouse.GetOldPositionX()))
				//static_cast<float>(mouse.GetOldPositionY());
			{
				if (static_cast<float>(mouse.GetOldPositionY()) < ui->Uiposition.y + ui->Uisize.y
					&& ui->Uiposition.y < static_cast<float>(mouse.GetOldPositionY()))
				{
					ui->UiColor = { 0.5f,0.5f,0.5f,1.0f };
					if (mouse.GetButtonDown() == mouse.BTN_LEFT && ui->NumDelivery[7] > 99)
					{
						ui->NumDelivery[6]++;

					}
				}

			}
			else
			{
				ui->UiColor = { 2.0f,2.0f,2.0f,1.0f };
			}
		}

		//値段
		ui->jank = ui->price;
		ui->junkDigits = 0;
		while (ui->jank != 0)
		{
			ui->jank /= 10;
			// 割った回数をカウント
			++ui->junkDigits;
		}
		ui->jankdig_ = ui->junkDigits;
		ui->jank = ui->price;
		if (ui->jank > 0)
		{
			for (int i = 0; i < ui->junkDigits; i++)
			{
				ui->saveJank[i] = ui->jank / pow(10, ui->jankdig_ - 1);
				ui->jankdig_--;
				int n = pow(10, ui->jankdig_ - 1);
				if (ui->jank > 10)
				{
					ui->jank -= ui->saveJank[i] * pow(10, ui->jankdig_);
				}
				int a = 0;
			}
		}
		else
		{
			ui->saveJank[0] = 0;
			ui->junkDigits = 1;
		}


		break;
	case 4:
		ui->player_MAXHP = ui->NumDelivery[2];
		ui->player_HP = ui->NumDelivery[1];

		for (int i = 0; i < ui->player_MAXHP; i++)
		{
			if (i > ui->player_HP - 1)
			{
				ui->HPUiColor[i] = { 0.5f,0.5f,0.5f,1.0f };

			}
			else
			{
				ui->HPUiColor[i] = { 1.2f,1.2f,1.2f,1.0f };
			}
		}
		break;
	case 5:
		ui->Uiposition = { 1280 / 2 - ui->Uisize.x / 2, 720 - ui->Uisize.y };
		if (static_cast<float>(mouse.GetOldPositionX()) < ui->Uiposition.x + ui->Uisize.x
			&& ui->Uiposition.x < static_cast<float>(mouse.GetOldPositionX()))
			//static_cast<float>(mouse.GetOldPositionY());
		{
			if (static_cast<float>(mouse.GetOldPositionY()) < ui->Uiposition.y + ui->Uisize.y
				&& ui->Uiposition.y < static_cast<float>(mouse.GetOldPositionY()))
			{
				ui->UiColor = { 0.5f,0.5f,0.5f,1.0f };
				if (mouse.GetButtonDown() == mouse.BTN_LEFT)
				{
					if (ui->NumDelivery[6] == 0)
					{
						ui->NumDelivery[6]++;
					}
					else
					{
						ui->NumDelivery[6] = 0;
					}
				}
			}
			else
			{
				ui->UiColor = { 1.0f,1.0f,1.0f,1.0f };
			}
		}
		break;
	case 6:
		ui->jank = ui->NumDelivery[1];
		ui->junkDigits = 0;
		while (ui->jank != 0)
		{
			ui->jank /= 10;
			// 割った回数をカウント
			++ui->junkDigits;
		}
		int jankdig_2 = ui->junkDigits;
		ui->jank = ui->NumDelivery[1];
		if (ui->jank > 0)
		{
			for (int i = 0; i < ui->junkDigits; i++)
			{
				ui->saveJank[i] = ui->jank / pow(10, ui->jankdig_ - 1);
				ui->jankdig_--;
				int n = pow(10, jankdig_2 - 1);
				if (ui->jank > 10)
				{
					ui->jank -= ui->saveJank[i]*pow(10, ui->jankdig_);
				}
				int a = 0;
			}
		}
		else
		{
			ui->saveJank[0] = 0;
			ui->junkDigits = 1;
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
			UiBase[2]->render(immediate_context, ui->Uiposition.x, ui->Uiposition.y, ui->Uisize.x, ui->Uisize.y, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0));
			UiBase[1]->render(immediate_context, ui->Uiposition3.x, ui->Uiposition3.y, 20,30, ui->HPUiColor[0].x, ui->HPUiColor[0].y, ui->HPUiColor[0].z, ui->HPUiColor[0].w, (0));
			//level用
			UiBase[3]->render(immediate_context, ui->Uiposition3.x, ui->Uiposition3.y, ui->Uisize3.x, ui->Uisize3.y, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0), 134.6 * ui->NumDelivery[3], 0, 134.6, 211);
			for (int i = 0; i < ui->junkDigits; i++)
			{
				//値段用
				UiBase[3]->render(immediate_context, ui->Uiposition2.x + i * (ui->Uisize2.x + 5), ui->Uiposition2.y, ui->Uisize2.x, ui->Uisize2.y, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0), 134.6 * ui->saveJank[i], 0, 134.6, 211);
			}
		}
		break;
	case 3:
		if (ui->NumDelivery[5] == 1)
		{
			UiBase[0]->render(immediate_context, 0, 0, 1280.0f, 720.0f, 1.0f, 1.0f, 1.0f, 0.9f, (0));
			
		}
		break;
	case 4:
		for (int i = 0; i < ui->player_MAXHP;i++)
		{
			UiBase[0]->render(immediate_context, 20.0f+27.0f*i, 15.0f, 40.0f, 50.0f, ui->HPUiColor[i].x, ui->HPUiColor[i].y, ui->HPUiColor[i].z, ui->HPUiColor[i].w, (0));
		}
		break;
	case 5:
			
			UiBase[0]->render(immediate_context, ui->Uiposition.x, ui->Uiposition.y,ui->Uisize.x, ui->Uisize.y, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0));
		break;
	case 6:
			
			UiBase[0]->render(immediate_context, ui->Uiposition.x+(ui->Uisize2.x*ui->junkDigits), ui->Uiposition.y,ui->Uisize.x, ui->Uisize.y, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0));
			for (int i = 0; i < ui->junkDigits;i++)
			{
				UiBase[1]->render(immediate_context, ui->Uiposition2.x + i*(ui->Uisize2.x+5), ui->Uiposition2.y, ui->Uisize2.x, ui->Uisize2.y, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0), 134.6 *ui->saveJank[i], 0, 134.6, 211);
			}
		break;
	}


}