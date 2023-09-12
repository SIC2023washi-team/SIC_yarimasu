#include "UI.h"
#include "SceneGame.h"
#include <imgui.h>




void UiInputComponent::Update(GameObject* gameobj, float elapsedTime)
{
}

void UiPhysicsComponent::Initialize(GameObject* gameobj)
{
	Ui* ui = dynamic_cast<Ui*> (gameobj);
	HRESULT hr{ S_OK };

	hr = XAudio2Create(ui->xaudio2.GetAddressOf(), 0, XAUDIO2_DEFAULT_PROCESSOR);
	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

	hr = ui->xaudio2->CreateMasteringVoice(&ui->master_voice);
	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

	ui->shop = std::make_unique<Lemur::Audio::audio>(ui->xaudio2.Get(), L".\\resources\\Audio\\SE\\shop.wav");
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
	case 1:
		UiBase[0] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\shadow.png");
		break;
	case 2:
		UiBase[0] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\UiBase.png");
		UiBase[2] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\junk.png");
		UiBase[3] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\font.png");
		UiBase[5] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\Lv.png");
		ui->Uisize = { 200.0f,200.0f };
		ui->Uiposition.x = 300.0 + 250 * ui->NumDelivery[1];
		ui->Uiposition.y = 130.0f;
		ui->Uiposition_[1].x = 407.0 + 250 * ui->NumDelivery[1];
		ui->Uiposition_[1].y = 303;
		ui->Uisize_[1] = { 16,22 };
		ui->Uiposition_[2].x = 380.0 + 250 * ui->NumDelivery[1];
		ui->Uiposition_[2].y = 302;
		ui->Uisize_[2] = { 28,26 };
	
		switch (ui->NumDelivery[2])
		{
		case 0:
			//攻撃速度
			UiBase[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\attack_speed.png");
			UiBase[4] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\attckspeedUp.png");
			ui->price = 100 * ui->NumDelivery[3];
			break;

		case 1:
			//弾速度
			UiBase[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\bullet_velocity.png");
			UiBase[4] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\SpeedUp.png");
			ui->price = 100 * ui->NumDelivery[3];
			break;
		case 2:
			//貫通力
			UiBase[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\penetration_force.png");
			UiBase[4] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\bretHPUp.png");
			ui->price = 250 + 50 * ui->NumDelivery[3];
			break;
		case 3:
			//攻撃力
			UiBase[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\offensive_power.png");
			UiBase[4] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\powerUp.png");
			ui->price = 100*ui->NumDelivery[3];
			break;
		case 4:
			//HP
			UiBase[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\HP.png");
			UiBase[4] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\HPUp.png");
			ui->price = 100 * ui->NumDelivery[3];
			break;
		case 5:
			//回復
			UiBase[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\heal.png");
			UiBase[4] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\healicon.png");
			ui->price = 100;
			break;
		}

		break;
	case 3:
		UiBase[0] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\pause.png");
		break;
	case 4:
		UiBase[0] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\HP_bit.png");
		break;
	case 5:
		UiBase[0] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\return.png");
		UiBase[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\SHOP.png");
		ui->Uisize = { 130.0f, 60.0f };
		ui->Uisize2 = { 400.0f, 30.0f };
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
	case 7:
		UiBase[0] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\WAVE.png");
		UiBase[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\font.png");
		ui->Uiposition2 = { 570,20 };
		ui->Uisize2 = { 20,45 };
		ui->Uiposition = { 560,10 };
		ui->Uisize = { 140,65 };
		break;
	case 8://リザルト
		UiBase[0] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\result.png");
		
		UiBase[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\font.png");
		UiBase[2] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\backtitle.png");
		ui->Uiposition_[0] = { 30,680 };
		ui->Uisize_[0] = { 150,65 };
		
		break;
	case 9:
		UiBase[0] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\font.png");
		UiBase[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\Lv.png");
		//攻撃速度
		Uiitem[0] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\attckspeedUp.png");
		Uiitem[1] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\SpeedUp.png");
		Uiitem[2] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\bretHPUp.png");
		Uiitem[3] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\powerUp.png");
		Uiitem[4] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\HPUp.png");
		//Uiitem[5] = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\Image\\healicon.png");
		
		ui->Uiposition_[0] = { 100,195 };
		ui->Uisize_[0] = { 15,30 };
		ui->Uiposition_[1] = { 60,190 };
		ui->Uisize_[1] = { 30,40 };
		ui->Uiposition_[2] = { 15,185 };
		ui->Uisize_[2] = { 45,45 };
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
					if (mouse.GetButtonDown() == mouse.BTN_LEFT && ui->NumDelivery[7] >= ui->price && ui->NumDelivery[3] < ui->NumDelivery[4])
					{
						ui->NumDelivery[6]++;
						ui->UiColor = { 2.0f,2.0f,2.0f,1.0f };

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


		//leval
		ui->jank = ui->NumDelivery[3];
		ui->levelDigits = 0;
		while (ui->jank != 0)
		{
			ui->jank /= 10;
			// 割った回数をカウント
			++ui->levelDigits;
		}
		ui->jankdig_ = ui->levelDigits;
		ui->jank = ui->NumDelivery[3];
		if (ui->jank > 0)
		{
			for (int i = 0; i < ui->levelDigits; i++)
			{
				ui->savelevel[i] = ui->jank / pow(10, ui->jankdig_ - 1);
				ui->jankdig_--;
				int n = pow(10, ui->jankdig_ - 1);
				if (ui->jank > 10)
				{
					ui->jank -= ui->savelevel[i] * pow(10, ui->jankdig_);
				}
				int a = 0;
			}
		}
		else
		{
			ui->savelevel[0] = 0;
			ui->levelDigits = 1;
		}



		ui->Uiposition2 = { 345.0f + 250.0f * ui->NumDelivery[1],280.0f };
		ui->Uisize2 = { 13,22 };
		//ジャンク
		ui->Uiposition_[0].x = 355.0 + 250 * ui->NumDelivery[1];
		ui->Uiposition_[0].y = 285.0f;
		ui->Uisize_[0] = { 60,20 };

		ui->NumDelivery[9] = ui->price;
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
		ui->Uiposition = { 1280 - ui->Uisize.x, 720 - ui->Uisize.y };
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
						ui->UiColor = { 1.2f,1.2f,1.2f,1.0f };
					}
					else
					{
						ui->NumDelivery[6] = 0;
						ui->UiColor = { 1.2f,1.2f,1.2f,1.0f };
					}
					ui->shop->play();
				}
			}
			else
			{
				ui->UiColor = { 1.2f,1.2f,1.2f,1.0f };
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
		ui->jankdig_ = ui->junkDigits;
		ui->jank = ui->NumDelivery[1];
		if (ui->jank > 0)
		{
			for (int i = 0; i < ui->junkDigits; i++)
			{
				ui->saveJank[i] = ui->jank / pow(10, ui->jankdig_ - 1);
				ui->jankdig_--;
				int n = pow(10, ui->jankdig_ - 1);
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
	case 7:
		ui->jank = ui->NumDelivery[3];
		ui->junkDigits = 0;
		while (ui->jank != 0)
		{
			ui->jank /= 10;
			// 割った回数をカウント
			++ui->junkDigits;
		}
		ui->jankdig_ = ui->junkDigits;
		ui->jank = ui->NumDelivery[3];
		if (ui->jank > 0)
		{
			for (int i = 0; i < ui->junkDigits; i++)
			{
	
				ui->saveJank[i] = ui->jank / pow(10, ui->jankdig_ - 1);
				
				int n = pow(10, ui->jankdig_ - 1);
				if (ui->jank > 10)
				{
					ui->jank -= ui->saveJank[i] * pow(10, ui->jankdig_-1);
				}
				ui->jankdig_--;
			}
		}
		else
		{
			ui->saveJank[0] = 0;
			ui->junkDigits = 1;
		};
	case 8:
		if (ui->NumDelivery[3])
		{
			if (static_cast<float>(mouse.GetOldPositionX()) < ui->Uiposition_[0].x + ui->Uisize_[0].x
				&& ui->Uiposition_[0].x < static_cast<float>(mouse.GetOldPositionX()))
				//static_cast<float>(mouse.GetOldPositionY());
			{
				if (static_cast<float>(mouse.GetOldPositionY()) < ui->Uiposition_[0].y + ui->Uisize_[0].y
					&& ui->Uiposition_[0].y < static_cast<float>(mouse.GetOldPositionY()))
				{
					ui->UiColor = { 0.5f,0.5f,0.5f,1.0f };
					if (mouse.GetButtonDown() == mouse.BTN_LEFT)
					{
						ui->NumDelivery[9] = 1;

					}
				}
				else
				{
					ui->UiColor = { 1.0f,1.0f,1.0f,1.0f };
				}
			}
		}
		break;
	case 9:
		for (int j = 0; j < 5; j++)
		{
			ui->jank = ui->itemLevelsave[j];
			ui->junkDigits = 0;
			while (ui->jank != 0)
			{
				ui->jank /= 10;
				// 割った回数をカウント
				++ui->junkDigits;
			}
			ui->jankdig_ = ui->junkDigits;
			ui->laveldig_[j] = ui->junkDigits;
			ui->jank = ui->itemLevelsave[j];
			if (ui->jank > 0)
			{
				for (int i = 0; i < ui->junkDigits; i++)
				{

					ui->savelavel_min[j][i] = ui->jank / pow(10, ui->jankdig_ - 1);

					int n = pow(10, ui->jankdig_ - 1);
					if (ui->jank > 10)
					{
						ui->jank -= ui->saveJank[i] * pow(10, ui->jankdig_ - 1);
					}
					ui->jankdig_--;
				}
			}
			else
			{
				ui->savelavel_min[j][0] = 0;
				ui->laveldig_[j] = 1;
			};

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
	case 1:
		UiBase[0]->render(immediate_context, 0, 0, 1280.0f, 720.0f, 1.0f, 1.0f, 1.0f, 0.5f, (0));
		break;
	case 2:
		if (ui->NumDelivery[5] == 1)
		{
			UiBase[0]->render(immediate_context, ui->Uiposition.x, ui->Uiposition.y, ui->Uisize.x, ui->Uisize.y, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0));
			UiBase[4]->render(immediate_context, ui->Uiposition.x+5, ui->Uiposition.y+5, ui->Uisize.x-5, ui->Uisize.y-5, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, 0.3f, (0));
			UiBase[1]->render(immediate_context, ui->Uiposition.x, ui->Uiposition.y, ui->Uisize.x, ui->Uisize.y, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0));
			UiBase[2]->render(immediate_context, ui->Uiposition_[0].x+(ui->Uisize2.x * ui->junkDigits), ui->Uiposition_[0].y, ui->Uisize_[0].x, ui->Uisize_[0].y, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0));
			for (int i = 0; i < ui->junkDigits; i++)
			{
			//値段用
			UiBase[3]->render(immediate_context, ui->Uiposition2.x + i * (ui->Uisize2.x + 5), ui->Uiposition2.y, ui->Uisize2.x, ui->Uisize2.y, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0), 134.6 * ui->saveJank[i], 0, 134.6, 211);
			}
			
			
			////level用
			
			UiBase[3]->render(immediate_context, ui->Uiposition_[1].x, ui->Uiposition_[1].y, ui->Uisize_[1].x, ui->Uisize_[1].y, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0), 134.6 * ui->NumDelivery[3], 0, 134.6, 211);
			UiBase[5]->render(immediate_context, ui->Uiposition_[2].x, ui->Uiposition_[2].y, ui->Uisize_[2].x, ui->Uisize_[2].y, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0));
	
		}
		break;
	case 3:
		if (ui->NumDelivery[5] == 1)
		{
			UiBase[0]->render(immediate_context, 0, 0, 1280.0f, 720.0f, 1.0f, 1.0f, 1.0f, 0.9f, (0));

		}
		break;
	case 4:
		for (int i = 0; i < ui->player_MAXHP; i++)
		{
			UiBase[0]->render(immediate_context, 20.0f + 27.0f * i, 15.0f, 35.0f, 50.0f, ui->HPUiColor[i].x, ui->HPUiColor[i].y, ui->HPUiColor[i].z, ui->HPUiColor[i].w, (0));
		}
		break;
	case 5:

		//UiBase[0]->render(immediate_context, ui->Uiposition.x, ui->Uiposition.y, ui->Uisize.x, ui->Uisize.y, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0));
		UiBase[1]->render(immediate_context, ui->Uiposition.x, ui->Uiposition.y, ui->Uisize.x, ui->Uisize.y, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0));
		break;
	case 6:

		UiBase[0]->render(immediate_context, ui->Uiposition.x + (ui->Uisize2.x * ui->junkDigits), ui->Uiposition.y, ui->Uisize.x, ui->Uisize.y, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0));
		for (int i = 0; i < ui->junkDigits; i++)
		{
			UiBase[1]->render(immediate_context, ui->Uiposition2.x + i * (ui->Uisize2.x + 5), ui->Uiposition2.y, ui->Uisize2.x, ui->Uisize2.y, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0), 134.6 * ui->saveJank[i], 0, 134.6, 211);
		}
		break;
	case 7:

		UiBase[0]->render(immediate_context, ui->Uiposition.x + (ui->Uisize2.x * ui->junkDigits), ui->Uiposition.y, ui->Uisize.x, ui->Uisize.y, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0));
		for (int i = 0; i < ui->junkDigits; i++)
		{
			UiBase[1]->render(immediate_context, ui->Uiposition2.x + i * (ui->Uisize2.x + 5), ui->Uiposition2.y, ui->Uisize2.x, ui->Uisize2.y, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0), 134.6 * ui->saveJank[i], 0, 134.6, 211);
		}
		break;
	case 8:
		if (ui->NumDelivery[3] == 1)
		{
			UiBase[0]->render(immediate_context, 0, 0, 1280.0f, 720.0f, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0));
			UiBase[1]->render(immediate_context, ui->Uiposition_[0].x, ui->Uiposition_[0].y, ui->Uisize_[0].x, ui->Uisize_[0].y, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0));
		}
		break;
	case 9:
		if (ui->NumDelivery[5] == 1)
		{
			for (int i = 0; i < 5; i++)
			{
				int num = i;
				for (int j = 0; j < ui->laveldig_[i]; j++)
				{
					j = j;
					//値段用
					UiBase[0]->render(immediate_context, ui->Uiposition_[0].x + j * (ui->Uisize_[0].x), ui->Uiposition_[0].y+50*i, ui->Uisize_[0].x, ui->Uisize_[0].y, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0), 134.6 * ui->savelavel_min[i][j], 0, 134.6, 211);
				}
				UiBase[1]->render(immediate_context, ui->Uiposition_[1].x, ui->Uiposition_[1].y + 50 * i, ui->Uisize_[1].x, ui->Uisize_[1].y, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0));
				Uiitem[i]->render(immediate_context, ui->Uiposition_[2].x, ui->Uiposition_[2].y + 50 * i, ui->Uisize_[2].x, ui->Uisize_[2].y, ui->UiColor.x, ui->UiColor.y, ui->UiColor.z, ui->UiColor.w, (0));
			}
		}
		break;
	}


}