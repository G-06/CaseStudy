//*****************************************************************************
//
// normal stage
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "normal_stage.h"
#include "stage_factory.h"
#include "../game_player.h"
#include "object/map.h"
#include "object/stage_offset.h"
#include "../../factory/scene_factory.h"
#include "system/system.h"
#include "../gimmick/gimmick_start_point.h"
#include "../gimmick/gimmick_check_point.h"
#include "../gimmick/gimmick_goal_point.h"
#include "../gimmick/gimmick_obstacle.h"
#include "../gimmick/gimmick_disappear_ground.h"
#include "../gimmick/gimmick_move_ground.h"
#include "../gimmick/gimmick_lens.h"
#include "../gimmick/gimmick_tutorial_text.h"
#include "../gimmick/gimmick_massage.h"


#include "object/object_light_gauge.h"
#include "object/object_player_icon.h"
#include "object/object_player_life .h"
#include "collision/collision_map.h"
#include "object/pause/pause.h"
#include "object/message_window.h"
#include "../game_bg.h"
#include "../effect/effect.h"
#include "../effect/effect_check_point.h"
#include "../assert_effect/assert_effect_start.h"
#include "../assert_effect/assert_effect_clear.h"
#include "../assert_effect/assert_effect_gameover.h"

#include "../effect/effect_mirror.h"
#include "../effect/effect_skeleton.h"
#include "../effect/effect_lens.h"
#include "object/stage_select/select_record.h"
#include "object/option.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 NormalStage::DEFAULT_LIGHT_GAUGE_POSITION = D3DXVECTOR2(40.0f,70.0f);
const D3DXVECTOR2 NormalStage::DEFAULT_PLAYER_ICON_POSITION = D3DXVECTOR2(21.0f,65.0f);
const D3DXVECTOR2 NormalStage::DEFAULT_PLAYER_LIFE_POSITION = D3DXVECTOR2(180.0f,40.0f);
const D3DXVECTOR2 NormalStage::DEFAULT_TIMER_POSITION =		  D3DXVECTOR2(DEFAULT_SCREEN_WIDTH - 220.0f,50.0f);
const f32 NormalStage::DEFAULT_LENS_ACCEL_SPEED = 1.1f;
const u32 DEST_FRAME_COUNT = 20;
static const u32 GAMEOVER_TIME = 50;	//ゲームプレイヤーの死ぬ時間プラスアルファな時間
const u32 NormalStage::NEXT_SCENE_TIME = 300;

//=============================================================================
// constructor
//=============================================================================
NormalStage::NormalStage(const TYPE& type)
	:Stage(type)
	,game_player_(nullptr)
	,map_(nullptr)
	,is_pause_(false)
	,is_clear_(false)
	,is_start_(true)
	,is_option_(false)
	,is_pause_input_(false)
	,stage_offset_(nullptr)
	,object_light_gauge_(nullptr)
	,object_player_icon_(nullptr)
	,object_player_life_(nullptr)
	,pause_(nullptr)
	,option_(nullptr)
	,message_window_(nullptr)
	,assert_effect_start_(nullptr)
	,assert_effect_clear_(nullptr)
	,select_record_(nullptr)
	,game_bg_(nullptr)
	,time_count_(0)
	,position_(0.0f,0.0f)
	,effect_timer_(0)
	,gameover_(false)
	,warp_(false)
{
	type_ = type;
}

//=============================================================================
// destructor
//=============================================================================
NormalStage::~NormalStage(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool NormalStage::Initialize(void)
{
	game_player_ = new GamePlayer();

	if(!SafeInitialize(game_player_))
	{
		return false;
	}
	game_player_->__position(D3DXVECTOR2(100.0f,0.0f));

	stage_offset_ = new StageOffset();

	object_light_gauge_ = new ObjectLightGauge();
	object_light_gauge_->Initialize();
	object_light_gauge_->__position(DEFAULT_LIGHT_GAUGE_POSITION);

	object_player_icon_ = new ObjectPlayerIcon();
	object_player_icon_->Initialize();
	object_player_icon_->__position(DEFAULT_PLAYER_ICON_POSITION);

	object_player_life_ = new ObjectPlayerLife();
	object_player_life_->Initialize();
	object_player_life_->__position(DEFAULT_PLAYER_LIFE_POSITION);

	if(!SafeInitialize(stage_offset_))
	{
		return false;
	}

	stage_offset_->__screen_size(D3DXVECTOR2((f32)DEFAULT_SCREEN_WIDTH,(f32)DEFAULT_SCREEN_HEIGHT));

	pause_ = new Pause();
	pause_->Initialize();

	message_window_ = new MessageWindow();
	message_window_->Initialize();
	message_window_->__dest_frame_count(DEST_FRAME_COUNT);

	// haikei
	game_bg_ = new GameBg();
	game_bg_->Initialize();
	game_bg_->__SetTexture(type_);

	//レコード
	time_count_ = 0;
	select_record_ = new SelectRecord();
	select_record_->Initialize();
	select_record_->__set_time(time_count_);
	select_record_->__set_position(DEFAULT_TIMER_POSITION);
	select_record_->Update();

	assert_effect_start_ = new AssertEffectStart();
	assert_effect_start_->Initialize();
	assert_effect_start_->__is_assert(true);

	assert_effect_clear_ = new AssertEffectClear();
	assert_effect_clear_->Initialize();
	assert_effect_clear_->set_record(select_record_);
	if(type_ == Stage::TYPE_TUTORIAL)
	{
		assert_effect_clear_->__is_tutorial(true);
	}
	assert_effect_GB_ = new AssertEffectGameover();
	assert_effect_GB_->Initialize();

	is_start_ = true;


	// option
	option_ = new Option();
	option_->Initialize();


	for(s32 i = 0; i < EFFECT_STOCK_NUM; i++)
	{
		effect_mirror_[i] = new EffectMirror();
		effect_mirror_[i]->Initialize();
		effect_skeleton_[i] = new EffectSkeleton();
		effect_skeleton_[i]->Initialize();
		effect_lens_[i] = new EffectLens();
		effect_lens_[i]->Initialize();
	}
	time =0;
	next_scene_timer_ = 0;

	if(type_ == Stage::TYPE_TUTORIAL)
	{
		GET_BGM->Play(BGM::BGM_ID_TUTORIAL);
	}
	else if(type_ == Stage::TYPE_STAGE10)
	{
		GET_BGM->Play(BGM::BGM_ID_CREDIT);
	}
	else if(type_ == Stage::TYPE_STAGE9)
	{
		GET_BGM->Play(BGM::BGM_ID_STAGE_03);
	}
	else
	{
		const int rand_bgm = rand() % 5;
		if(rand_bgm == 0)
		{
			GET_BGM->Play(BGM::BGM_ID_STAGE_01);
		}
		else if(rand_bgm == 1)
		{
			GET_BGM->Play(BGM::BGM_ID_STAGE_02);
		}
		else if(rand_bgm == 2)
		{
			GET_BGM->Play(BGM::BGM_ID_STAGE_03);
		}
		else if(rand_bgm == 3)
		{
			GET_BGM->Play(BGM::BGM_ID_STAGE_04);
		}
		else if(rand_bgm == 4)
		{
			GET_BGM->Play(BGM::BGM_ID_STAGE_05);
		}
		else
		{
			GET_BGM->Play(BGM::BGM_ID_STAGE_01);
		}
	}

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void NormalStage::Uninitialize(void)
{
	SafeRelease(game_player_);

	SafeRelease(map_);

	SafeRelease(stage_offset_);

	SafeRelease(object_light_gauge_);

	SafeRelease(object_player_icon_);

	SafeRelease(object_player_life_);

	SafeRelease(select_record_);

	SafeRelease(assert_effect_start_);

	SafeRelease(assert_effect_clear_);

	SafeRelease(assert_effect_GB_);

	for(auto it = gimmick_container_.begin();it != gimmick_container_.end();++it)
	{
		SafeRelease(*it);
	}
	gimmick_container_.clear();

	for(auto it = effect_container_.begin();it != effect_container_.end();++it)
	{
		SafeRelease(*it);
	}

	effect_container_.clear();

	SafeDelete(next_stage_factory_);

	SafeRelease(pause_);

	SafeRelease(message_window_);

	SafeRelease(game_bg_);

	SafeRelease(option_);

	for(s32 i = 0; i < EFFECT_STOCK_NUM; i++)
	{
		SafeRelease(effect_mirror_[i]);
		SafeRelease(effect_skeleton_[i]);
		SafeRelease(effect_lens_[i]);
	}
}

//=============================================================================
// update
//=============================================================================
void NormalStage::Update(void)
{
	//開始直後
	if(is_start_)
	{
		assert_effect_start_->Update();

		if(!assert_effect_start_->__is_assert())
		{
			is_start_ = false;
		}
	}
	//クリア時
	else if(is_clear_)
	{
		assert_effect_clear_->__is_assert(true);
		//プレイヤー更新
		game_player_->Update();

		// 笑顔
		object_player_icon_->__animation_index(ObjectPlayerIcon::ICON_TYPE_SMILE);
		object_player_icon_->Update();

		//ギミック更新
		for(auto it = gimmick_container_.begin();it != gimmick_container_.end();++it)
		{
			(*it)->Update();
		}

		// その他のエフェクト
		for(s32 i = 0; i < EFFECT_STOCK_NUM;i++)
		{
			if(!effect_mirror_[i]->__is_free())
			{
				effect_mirror_[i]->Update();
			}
			if(!effect_skeleton_[i]->__is_free())
			{
				effect_skeleton_[i]->Update();
			}
			if(!effect_lens_[i]->__is_free())
			{
				effect_lens_[i]->Update();
			}
		}

		//マップとの当たり判定？
		if(game_player_->__position().x + game_player_->__size().x * 0.5f > map_->__size().x)
		{
			game_player_->__position(D3DXVECTOR2(map_->__size().x - game_player_->__size().x * 0.5f,game_player_->__position().y));
		}
		//画面外横に行かない判定？
		if(game_player_->__position().x - game_player_->__size().x * 0.5f < 0)
		{
			game_player_->__position(D3DXVECTOR2(game_player_->__size().x * 0.5f,game_player_->__position().y));
		}
		for(auto it = gimmick_container_.begin();it != gimmick_container_.end();++it)
		{
			(*it)->__offset_position(stage_offset_->__position());
		}

		for(auto it = effect_container_.begin();it != effect_container_.end();++it)
		{
			(*it)->__offset_position(stage_offset_->__position());
		}

		//マップチップとの当たり判定
		CollisionChip();
		// offsetによる各オブジェクト類の位置更新
		stage_offset_->__reference_position(game_player_->__position());
		stage_offset_->Update();
		game_player_->__offset_position(stage_offset_->__position());
		map_->__position(-stage_offset_->__position());

		//レコード参照
		u32 oldRecord = System::RecordLoad((System::__get_current_stage()-1));
		//レコード比較
		if(time_count_<oldRecord)
		{
			System::RecordSave((System::__get_current_stage()-1),time_count_);

			if(type_ != TYPE_TUTORIAL)
			{
				assert_effect_clear_->__set_newrecord_flag(true);
			}
		}

		assert_effect_clear_->SetTime(time_count_);
		assert_effect_clear_->Update();

		if(assert_effect_clear_->__is_stop())
		{
			next_scene_timer_++;	//時間制限カウント

			if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_DECIDE)||next_scene_timer_>=NEXT_SCENE_TIME)
			{
				game_player_->__Set_status(GamePlayer::CAT_STATUS_WARP);
				warp_=true;
				is_clear_ = false;
				GET_SE->Play(SE::SE_ID_STAGE_START);
			}
		}
	}
	else if(warp_)
	{
		//プレイヤー更新
		game_player_->Update();

		//ギミック更新
		for(auto it = gimmick_container_.begin();it != gimmick_container_.end();++it)
		{
			(*it)->Update();
		}

		if(game_player_->__Get_warpout()==true)
		{
			if(next_stage_factory_ == nullptr)
			{
				next_stage_factory_ = new SelectFactory();
			}
		}
	}
	else if(gameover_)
	{
		// 怒り
		object_player_icon_->__animation_index(ObjectPlayerIcon::ICON_TYPE_ANGER);
		object_player_icon_->Update();

		// その他のエフェクト
		for(s32 i = 0; i < EFFECT_STOCK_NUM;i++)
		{
			if(!effect_mirror_[i]->__is_free())
			{
				effect_mirror_[i]->Update();
			}
			if(!effect_skeleton_[i]->__is_free())
			{
				effect_skeleton_[i]->Update();
			}
			if(!effect_lens_[i]->__is_free())
			{
				effect_lens_[i]->Update();
			}
		}

		if((time>=game_player_->DEAD_TIME+5))
		{

			assert_effect_GB_->__is_assert(true);
			assert_effect_GB_->Update();

			if((assert_effect_GB_->__is_stop()==true))
			{
				next_scene_timer_++;

				if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_DECIDE)||next_scene_timer_>=NEXT_SCENE_TIME)
				{
					if(next_stage_factory_ == nullptr)
					{
						next_stage_factory_ = new SelectFactory();
					}
				}
			}
		}
		else
		{
			game_player_->Update();
		}
		time++;
	}
	else if(game_player_->__life() <= 0)	//残機が尽きたとき
	{
		gameover_ = true;
	}
	else	//プレイヤーが生きてるゲーム中
	{
		//ポーズしているとき
		if(is_pause_)
		{
			//ポーズメニューが出てるとき
			if(!is_pause_input_ && !pause_->__is_move())
			{
				//オプション更新
				if(is_option_)
				{
					option_->Update();
					if(option_->__is_indication() == false){
						is_option_ = false;
						const s32 current_select = pause_->__is_select();
						pause_->__select_texture_id_(current_select, Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);
					}
				}
				else
				{
					//選択肢を選んでるとき
					if(message_window_->__is_show())
					{
						// メッセージの選択処理
						if(message_window_->__is_show()){

							if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_LEFT))
							{
								message_window_->SelectDown();
							}
							if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_RIGHT))
							{
								message_window_->SelectUp();
							}

							if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_DECIDE))
							{
								GET_SE->Play(SE::SE_ID_DECIDE);
								const s32 current_select = message_window_->__is_select();

								message_window_->__select_frame_texture_id_(current_select, Texture::TEXTURE_ID_TITLE_SELECT_FRAME_002);

								if(current_select == MessageWindow::MESSAGE_NO)
								{
									message_window_->Close();
									const s32 current_select = pause_->__is_select();
									pause_->__select_texture_id_(current_select, Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);
								}
								if((current_select == MessageWindow::MESSAGE_YES))
								{
									// select
									const s32 current_select = pause_->__is_select();
									switch(current_select)
									{
									case Pause::SELECT_TYPE_RETRY:
										{
											if(next_stage_factory_ == nullptr)
											{
												is_pause_input_ = true;
												next_stage_factory_ = CreateFactory();
											}
											break;
										}
									case Pause::SELECT_TYPE_STAGESELECT_BACK:
										{
											if(next_stage_factory_ == nullptr)
											{
							
												
												is_pause_input_ = true;
												next_stage_factory_ = new SelectFactory();
											}
											break;
										}
									} // switch
								} // message
							}
						} // is_show
					}
					else	//選択肢を選んでいないとき？
					{
						if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_UP))
						{
							pause_->SelectDown();
						}
						if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_DOWN))
						{
							pause_->SelectUp();
						}
						if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_DECIDE))
						{
							GET_SE->Play(SE::SE_ID_DECIDE);
							// select
							const s32 current_select = pause_->__is_select();
							pause_->__select_texture_id_(current_select, Texture::TEXTURE_ID_TITLE_SELECT_FRAME_002);
							switch(current_select)
							{
							case Pause::SELECT_TYPE_GAME_BACK:
								{
									is_pause_ = false;
									pause_->Close();
									break;
								}
							case Pause::SELECT_TYPE_RETRY:
								{
									message_window_->Show();
									message_window_->__title_texture_id_(Texture::TEXTURE_ID_PAUSE_STRUNG_CONFIRM_RETRY);
									break;
								}
							case Pause::SELECT_TYPE_STAGESELECT_BACK:
								{
									message_window_->Show();
									message_window_->__title_texture_id_(Texture::TEXTURE_ID_PAUSE_STRUNG_CONFIRM_SELECT);
									break;
								}
							case Pause::SELECT_TYPE_OPTION:
								{
									is_option_ = true;
									option_->__is_indication(true);
									break;
								}
							} // switch
						}
						if((GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_PAUSE) || GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_CANCEL)) && !pause_->__is_move())
						{
							is_pause_ = false;
							pause_->Close();
						}
					} // message_window
				} // is_option
			} // !pause_->__is_move()
		}
		//ゲームを遊んでいるときの更新
		else
		{
			//時間カウント
			time_count_++;
			//プレイヤー更新
			game_player_->Update();
			//プレイヤーアイコン更新
			object_player_icon_->Update();
			if(game_player_->__Get_status() != GamePlayer::CAT_STATUS_DEAD)
			{
				f32 light_rate = (f32)game_player_->__sp() / (f32)game_player_->__sp_max();
				if(light_rate >= 0.5f)
				{
					object_player_icon_->__animation_index(ObjectPlayerIcon::ICON_TYPE_NORMAL);
				}
				else
				{
					object_player_icon_->__animation_index(ObjectPlayerIcon::ICON_TYPE_CRY);
				}
			}
			else
			{
				object_player_icon_->__animation_index(ObjectPlayerIcon::ICON_TYPE_ANGER);
			}


			//ギミック更新
			for(auto it = gimmick_container_.begin();it != gimmick_container_.end();++it)
			{
				(*it)->Update();
			}
			//光化以外のエフェクト更新　光化はプレイヤーの中
			for(auto it = effect_container_.begin();it != effect_container_.end();++it)
			{
				(*it)->Update();
			}

			// その他のエフェクト
			for(s32 i = 0; i < EFFECT_STOCK_NUM;i++)
			{
				if(!effect_mirror_[i]->__is_free())
				{
					effect_mirror_[i]->Update();
				}
				if(!effect_skeleton_[i]->__is_free())
				{
					effect_skeleton_[i]->Update();
				}
				if(!effect_lens_[i]->__is_free())
				{
					effect_lens_[i]->Update();
				}
			}

			//ゲージサイズ計算
			object_light_gauge_->__rate((f32)game_player_->__sp() / (f32)game_player_->__sp_max() * 100.0f);
			//ゲージ更新
			object_light_gauge_->Update();
			//マップとの当たり判定？
			if(game_player_->__position().x + game_player_->__size().x * 0.5f > map_->__size().x)
			{
				game_player_->__position(D3DXVECTOR2(map_->__size().x - game_player_->__size().x * 0.5f,game_player_->__position().y));
			}
			//画面外横に行かない判定？
			if(game_player_->__position().x - game_player_->__size().x * 0.5f < 0)
			{
				game_player_->__position(D3DXVECTOR2(game_player_->__size().x * 0.5f,game_player_->__position().y));
			}
			//画面外死
			if(game_player_->__position().y > map_->__size().y)
			{
				game_player_->Dead();
				game_bg_->ReSetUv();
			}
			//ギミックとの当たり判定
			CollisionGimmick();
			//マップチップとの当たり判定
			CollisionChip();
			//残機の更新
			object_player_life_->__life(game_player_->__life());
			object_player_life_->Update();
			//エフェクトが死んだときの解放？
			auto predfunc = [](Effect* effect)->bool
			{
				if(effect->__is_death())
				{
					effect->Uninitialize();
					delete effect;
					return true;
				}
				return false;
			};

			// effect
			effect_container_.erase(remove_if(effect_container_.begin(),effect_container_.end(),predfunc),effect_container_.end());

			// offsetによる各オブジェクト類の位置更新
			stage_offset_->__reference_position(game_player_->__position());
			stage_offset_->Update();

			// player
			game_player_->__offset_position(stage_offset_->__position());

			// map
			map_->__position(-stage_offset_->__position());

			//背景更新
			game_bg_->__position(game_player_->__position());
			game_bg_->__position_player(game_player_->__position());
			game_bg_->__move(game_player_->__move());
			game_bg_->Update();

			for(auto it = gimmick_container_.begin();it != gimmick_container_.end();++it)
			{
				(*it)->__offset_position(stage_offset_->__position());
			}

			for(auto it = effect_container_.begin();it != effect_container_.end();++it)
			{
				(*it)->__offset_position(stage_offset_->__position());
			}

			 
			for(s32 i = 0;i < EFFECT_STOCK_NUM;i++)
			{
				if(!effect_mirror_[i]->__is_free())
				{
					effect_mirror_[i]->__offset_position(stage_offset_->__position());
				}
				if(!effect_skeleton_[i]->__is_free())
				{
					effect_skeleton_[i]->__offset_position(stage_offset_->__position());
				}
				if(!effect_lens_[i]->__is_free())
				{
					effect_lens_[i]->__offset_position(stage_offset_->__position());
				}
			}

			if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_PAUSE) && !pause_->__is_move())
			{
				is_pause_ = true;
				pause_->Show();
			}
		}	//ポーズしているとき

		select_record_->__set_time(time_count_);
		select_record_->Update();
		pause_->Update();
		message_window_->Update();
	}

#ifndef _RELEASE
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_R))
	{
		Uninitialize();
		Initialize();
	}
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_C))
	{
		is_clear_ = true;
		game_player_->Clear();

	}

#endif
}

//=============================================================================
// draw
//=============================================================================
void NormalStage::Draw(void)
{
	game_bg_->Draw();
	map_->Draw();

	for(auto it = gimmick_container_.begin();it != gimmick_container_.end();++it)
	{
		if(((*it)->__type()!=Gimmick::TYPE_TUTORIAL_TEXT)&&((*it)->__type()!=Gimmick::TYPE_MASSAGE))
		{
			(*it)->Draw();
		}
	}

	for(auto it = effect_container_.begin();it != effect_container_.end();++it)
	{
		(*it)->Draw();
	}

	object_light_gauge_->Draw();
	object_player_icon_->Draw();
	object_player_life_->Draw();

	if(type_!=Stage::TYPE_TUTORIAL)
	{
		select_record_->Draw();
	}

	for(auto it = gimmick_container_.begin();it != gimmick_container_.end();++it)
	{
		if(((*it)->__type()==Gimmick::TYPE_TUTORIAL_TEXT)||((*it)->__type()==Gimmick::TYPE_MASSAGE))
		{
			(*it)->Draw();
		}
	}

	game_player_->Draw();


	for(s32 i = 0; i < EFFECT_STOCK_NUM;i++)
	{
		if(!effect_mirror_[i]->__is_free())
		{
			effect_mirror_[i]->Draw();
		}
		if(!effect_skeleton_[i]->__is_free())
		{
			effect_skeleton_[i]->Draw();
		}
		if(!effect_lens_[i]->__is_free())
		{
			effect_lens_[i]->Draw();
		}
	}


	assert_effect_start_->Draw();
	assert_effect_GB_->Draw();
	assert_effect_clear_->Draw();

	pause_->Draw();
	message_window_->Draw();

	option_->Draw();
}

//=============================================================================
// collision chip
//=============================================================================
void NormalStage::CollisionChip(void)
{
	D3DXVECTOR2 player_position = game_player_->__position();
	D3DXVECTOR2 player_old_position = game_player_->__old_position();
	D3DXVECTOR2 index_position;
	u32 index = 0;
	CollisionMap collision_map;

	// 下
	index = map_->GetIndex(D3DXVECTOR2(player_position.x,player_position.y + game_player_->__size().y * 0.5f),&index_position);

	CollisionChip(index,index_position);

	// 右
	index = map_->GetIndex(D3DXVECTOR2(player_position.x + game_player_->__size().x * 0.5f,player_position.y),&index_position);

	CollisionChip(index,index_position);

	// 左
	index = map_->GetIndex(D3DXVECTOR2(player_position.x - game_player_->__size().x * 0.5f,player_position.y),&index_position);

	CollisionChip(index,index_position);

	// 上
	index = map_->GetIndex(D3DXVECTOR2(player_position.x,player_position.y - game_player_->__size().y * 0.5f),&index_position);

	CollisionChip(index,index_position);

	// 右下
	index = map_->GetIndex(D3DXVECTOR2(player_position.x + game_player_->__size().x * 0.5f,player_position.y + game_player_->__size().y * 0.5f),&index_position);

	CollisionChip(index,index_position);

	// 左下
	index = map_->GetIndex(D3DXVECTOR2(player_position.x - game_player_->__size().x * 0.5f,player_position.y + game_player_->__size().y * 0.5f),&index_position);

	CollisionChip(index,index_position);

	// 右上
	index = map_->GetIndex(D3DXVECTOR2(player_position.x + game_player_->__size().x * 0.5f,player_position.y - game_player_->__size().y * 0.5f),&index_position);

	CollisionChip(index,index_position);

	// 左上
	index = map_->GetIndex(D3DXVECTOR2(player_position.x - game_player_->__size().x * 0.5f,player_position.y - game_player_->__size().y * 0.5f),&index_position);

	CollisionChip(index,index_position);

}

//=============================================================================
// collision chip
//=============================================================================
void NormalStage::CollisionChip(u32 index,const D3DXVECTOR2& position)
{
	CollisionMap collision_map;

	switch(index)
	{
		case 1:
		{
			if(collision_map.IsHit(game_player_->__position(),game_player_->__old_position(),position,game_player_->__size().x * 0.5f,game_player_->__size().y * 0.5f,128 * 0.5f,128 * 0.5f))
			{
				if(game_player_->__is_preview_light())
				{
					game_player_->Dead();
				}
				else
				{
					if(collision_map.__vector().y > 0)
					{
						game_player_->HitStage(collision_map.__position(),true);
					}
					else
					{
						game_player_->HitStage(collision_map.__position());
					}
				}
			}
			break;
		}
		case 2:
		{
			if(collision_map.IsHit(game_player_->__position(),game_player_->__old_position(),position,game_player_->__size().x * 0.5f,game_player_->__size().y * 0.5f,128 * 0.5f,128 * 0.5f))
			{
				if(game_player_->__is_preview_light())
				{
					game_player_->Dead();
				}
				else
				{
					if(collision_map.__vector().y > 0)
					{
						game_player_->HitStage(collision_map.__position(),true);
					}
					else
					{
						game_player_->HitStage(collision_map.__position());
					}
				}
			}
			break;
		}
		case 3://鏡
		{
			if(collision_map.IsHit(game_player_->__position(),game_player_->__old_position(),position,game_player_->__size().x * 0.5f,game_player_->__size().y * 0.5f,128 * 0.5f,128 * 0.5f))
			{
				if(game_player_->__is_light())
				{
					const D3DXVECTOR2 position = game_player_->__position();

					game_player_->__position(collision_map.__position());
					GET_SE->Play(SE::SE_ID_REFLECTION);

					for(s32 i = 0; i < EFFECT_STOCK_NUM; i++)
					{
						if(effect_mirror_[i]->__is_free())
						{
							effect_mirror_[i]->__position(position);
							effect_mirror_[i]->Start();
							break;
						}
					}

					if(collision_map.__vector().x != 0.0f)
					{
						game_player_->ChangeDirection(D3DXVECTOR2(-game_player_->__move().x,game_player_->__move().y));
					}
					else
					{
						game_player_->ChangeDirection(D3DXVECTOR2(game_player_->__move().x,-game_player_->__move().y));
					}
				}
				else
				{
					if(collision_map.__vector().y > 0)
					{
						game_player_->HitStage(collision_map.__position(),true);
					}
					else
					{
						game_player_->HitStage(collision_map.__position());
					}
				}
			}
			break;
		}
		case 4:
		{
			if(collision_map.IsHit(game_player_->__position(),game_player_->__old_position(),position,game_player_->__size().x * 0.5f,game_player_->__size().y * 0.5f,128 * 0.5f,128 * 0.5f))
			{
				if(game_player_->__is_light())
				{
					game_player_->__is_force_light(true);
					effect_timer_++;
					if(effect_timer_ % 20 == 0)
					{
						
						for(s32 i = 0; i < EFFECT_STOCK_NUM;i++)
						{
							if(effect_skeleton_[i]->__is_free())
							{
								effect_skeleton_[i]->__position(game_player_->__position());
								effect_skeleton_[i]->Start();
								break;
							}
						}
					}
				}
				else
				{
					effect_timer_ = 0;
					if(collision_map.__vector().y > 0)
					{
						game_player_->HitStage(collision_map.__position(),true);
					}
					else
					{
						game_player_->HitStage(collision_map.__position());
					}
				
				}
			}
			break;
		}
		case 5:		//死棘
		{
			if((game_player_->__Get_status()) == GamePlayer::CAT_STATUS_LIVE)
			{
				if(collision_map.IsHit(game_player_->__position(),game_player_->__old_position(),position,game_player_->__size().x * 0.5f,game_player_->__size().y * 0.5f,128 * 0.5f,128 * 0.5f))
				{
					game_player_->Dead();
				}
			}
			break;
		}
		case 6:		//死棘
		{
			if((game_player_->__Get_status()) == GamePlayer::CAT_STATUS_LIVE)
			{
				if(collision_map.IsHit(game_player_->__position(),game_player_->__old_position(),position,game_player_->__size().x * 0.5f,game_player_->__size().y * 0.5f,128 * 0.5f,128 * 0.5f))
				{
					game_player_->Dead();
				}
			}
			break;
		}
		case 7:		//死棘
		{
			if((game_player_->__Get_status()) == GamePlayer::CAT_STATUS_LIVE)
			{
				if(collision_map.IsHit(game_player_->__position(),game_player_->__old_position(),position,game_player_->__size().x * 0.5f,game_player_->__size().y * 0.5f,128 * 0.5f,128 * 0.5f))
				{
					game_player_->Dead();
				}
			}
			break;
		}
		case 8:		//死棘
		{
			if((game_player_->__Get_status()) == GamePlayer::CAT_STATUS_LIVE)
			{
				if(collision_map.IsHit(game_player_->__position(),game_player_->__old_position(),position,game_player_->__size().x * 0.5f,game_player_->__size().y * 0.5f,128 * 0.5f,128 * 0.5f))
				{
					game_player_->Dead();
				}
			}
			break;
		}
		case 9:
		{
			if(collision_map.IsHit(game_player_->__position(),game_player_->__old_position(),position,game_player_->__size().x * 0.5f,game_player_->__size().y * 0.5f,128 * 0.5f,128 * 0.5f))
			{
				game_player_->__is_sp_recover_speed_up(true);
			}
			break;
		}
		case 10:
		{
			if(collision_map.IsHit(game_player_->__position(),game_player_->__old_position(),position,game_player_->__size().x * 0.5f,game_player_->__size().y * 0.5f,128 * 0.5f,128 * 0.5f))
			{
				game_player_->__is_sp_down(true);
			}
			break;
		}
		default:
		{
			break;
		}
	}
}

//=============================================================================
// collision gimmick
//=============================================================================
void NormalStage::CollisionGimmick(void)
{
	for(auto it = gimmick_container_.begin();it != gimmick_container_.end();++it)
	{
		D3DXVECTOR2 player_position = game_player_->__position();
		D3DXVECTOR2 player_old_position = game_player_->__old_position();
		D3DXVECTOR2 player_size = game_player_->__size() * 0.5f;
		D3DXVECTOR2 gimmick_position = (*it)->__position();
		D3DXVECTOR2 gimmick_size = (*it)->__size() * 0.5f;
		CollisionMap collision_map;

		if(collision_map.IsHit(player_position,player_old_position,gimmick_position,player_size.x,player_size.y,gimmick_size.x,gimmick_size.y))
		{
			switch((*it)->__type())
			{
				case Gimmick::TYPE_CHECK_POINT:
				{
					DEBUG_TOOL.__debug_display()->Print("hit check point\n");
					GimmickCheckPoint::DATA* data = (GimmickCheckPoint::DATA*)(*it)->GetPointer();
					if(game_player_->__check_point_priority() < data->_priority)
					{
						GET_SE->Play(SE::SE_ID_CHECK_POINT);
						data->_hit = true;
						game_player_->__check_point_priority(data->_priority);
						game_player_->__return_position(gimmick_position);
						game_player_->Heal(1);
						EffectCheckPoint* effect = new EffectCheckPoint();
						effect->Initialize();
						const D3DXVECTOR2 check_point_position = D3DXVECTOR2(gimmick_position.x,gimmick_position.y - 150.0f);
						effect->__position(check_point_position);
						effect_container_.push_back(effect);
					}
					break;
				}
				case Gimmick::TYPE_GOAL_POINT:
				{
					GET_SE->Play(SE::SE_ID_GOAL);
					DEBUG_TOOL.__debug_display()->Print("hit goal point\n");
					is_clear_ = true;
					game_player_->Clear();
					break;
				}
				case Gimmick::TYPE_OBSTACLE:
				{
					DEBUG_TOOL.__debug_display()->Print("hit obstacle\n");
					game_player_->Dead();
					break;
				}
				case Gimmick::TYPE_DISAPPEAR_GROUND:
				{
					GimmickDisappearGround::DATA* data = (GimmickDisappearGround::DATA*)(*it)->GetPointer();
					if(data->_is_hit)
					{
						DEBUG_TOOL.__debug_display()->Print("hit disappear ground\n");
						if(collision_map.__vector().y > 0)
						{
							game_player_->HitStage(collision_map.__position(),true);
						}
						else
						{
							game_player_->HitStage(collision_map.__position(),false);
						}
					}
					break;
				}
				case Gimmick::TYPE_MOVE_GROUND:
				{
					GimmickMoveGround::DATA* data = (GimmickMoveGround::DATA*)(*it)->GetPointer();

					if(collision_map.IsHit(player_position,player_old_position + data->_move,gimmick_position,player_size.x,player_size.y,gimmick_size.x,gimmick_size.y))
					{
						if(collision_map.__vector().y > 0)
						{
							game_player_->Accelerate(data->_move);
							game_player_->HitStage(collision_map.__position(),true);
						}
						else
						{
							game_player_->HitStage(collision_map.__position());
						}
						DEBUG_TOOL.__debug_display()->Print("hit move ground\n");
					}
					break;
				}
				case Gimmick::TYPE_LENS:
				{
					GimmickLens::DATA* data = (GimmickLens::DATA*)(*it)->GetPointer();

					if(collision_map.IsHit(player_position,player_old_position + data->_move,gimmick_position,player_size.x,player_size.y,gimmick_size.x,gimmick_size.y))
					{
						if(game_player_->__is_light())
						{
							//game_player_->__position(gimmick_position);
							

							//game_player_->__position(data->_shotposition);

							game_player_->ChangeDirection(data->_shotvec);
							if(game_player_->LightAccele(DEFAULT_LENS_ACCEL_SPEED))
							{
								GET_SE->Play(SE::SE_ID_REFLECTION);
								for(s32 i = 0; i < EFFECT_STOCK_NUM;i++)
								{
									if(effect_lens_[i]->__is_free())
									{
										effect_lens_[i]->__position(gimmick_position);
										effect_lens_[i]->Start();
										break;
									}
								}
							}
						}

						// 乗る判定
						
						//else if(collision_map.__vector().y > 0)
						//{
						//	game_player_->Accelerate(data->_move);
						//	game_player_->HitStage(collision_map.__position(),true);
						//}
						//else
						//{
						//	game_player_->HitStage(collision_map.__position());
						//}

						DEBUG_TOOL.__debug_display()->Print("hit lens\n");
					}
					break;
				}
				case Gimmick::TYPE_TUTORIAL_TEXT:
				{
					GimmickTutorialText::DATA* data = (GimmickTutorialText::DATA*)(*it)->GetPointer();
					data->_is_hit=true;
					DEBUG_TOOL.__debug_display()->Print("hit text\n");
					break;
				}
				case Gimmick::TYPE_MASSAGE:
				{
					GimmickMassage::DATA* data = (GimmickMassage::DATA*)(*it)->GetPointer();
					data->_is_hit=true;
					DEBUG_TOOL.__debug_display()->Print("hit massage\n");
					break;
				}
			}
		}
	}
}

//=============================================================================
// load from file
//=============================================================================
bool NormalStage::LoadFromFile(const s8* filename)
{
	s8* data;
	FILE* file = nullptr;
	u32 size;

	fopen_s(&file,filename,"rt");

	if(file == nullptr)
	{
		return false;
	}

	// get file size
	fseek(file,0,SEEK_END);
	size = ftell(file);
	fseek(file,0,SEEK_SET);

	// read data
	data = new s8[size + 1];
	fread(data,1,size,file);
	data[size] = '\n';

	// close file
	fclose(file);

	s8 word[256];
	u32 count = 0;

	for(u32 i = 0;i < size;++i)
	{
		if(data[i] == '/')
		{
			if(data[i + 1] == '/')
			{
				i += FindWord(word,&data[i],"\n");
				count = 0;
			}
		}
		else if(data[i] == ',')
		{
			word[count] = '\0';

			u32 type = atoi(word);
			i++;
			switch(type)
			{
				case Gimmick::TYPE_START_POINT:
				{
					i += FindWord(word,&data[i],",\n\0");
					f32 x = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 y = atof(word);

					GimmickStartPoint* gimmick = new GimmickStartPoint();
					gimmick->Initialize();
					gimmick->__position(D3DXVECTOR2(x,y));
					gimmick_container_.push_back(gimmick);
					game_player_->__position(D3DXVECTOR2(x,y));
					game_player_->__return_position(D3DXVECTOR2(x,y));
					stage_offset_->__reference_position(D3DXVECTOR2(x,y));
					stage_offset_->__position(D3DXVECTOR2(x - stage_offset_->__screen_size().x * 0.5f,y - stage_offset_->__screen_size().y * 0.5f));
					stage_offset_->Update();
					map_->__position(-stage_offset_->__position());
					game_bg_->__position(stage_offset_->__position());

					i += FindWord(word,&data[i],"\n\0");
					break;
				}
				case Gimmick::TYPE_CHECK_POINT:
				{
					i += FindWord(word,&data[i],",\n\0");
					f32 x = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 y = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					u32 priority = atoi(word);

					GimmickCheckPoint* gimmick = new GimmickCheckPoint();
					gimmick->Initialize();
					gimmick->__position(D3DXVECTOR2(x,y));
					gimmick->__priority(priority);
					gimmick_container_.push_back(gimmick);
					i += FindWord(word,&data[i],"\n\0");
					break;
				}
				case Gimmick::TYPE_GOAL_POINT:
				{
					i += FindWord(word,&data[i],",\n\0");
					f32 x = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 y = atof(word);

					GimmickGoalPoint* gimmick = new GimmickGoalPoint();
					gimmick->Initialize();
					gimmick->__position(D3DXVECTOR2(x,y));
					gimmick_container_.push_back(gimmick);
					i += FindWord(word,&data[i],"\n\0");
					break;
				}
				case Gimmick::TYPE_OBSTACLE:
				{
					i += FindWord(word,&data[i],",\n\0");
					f32 x = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 y = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 end_x = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 end_y = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 speed = atof(word);

					GimmickObstacle* gimmick = new GimmickObstacle();
					gimmick->Initialize();
					gimmick->__position(D3DXVECTOR2(x,y));
					gimmick->__start_position(D3DXVECTOR2(x,y));
					gimmick->__end_position(D3DXVECTOR2(end_x,end_y));
					gimmick->__speed(speed);
					gimmick_container_.push_back(gimmick);
					i += FindWord(word,&data[i],"\n\0");
					break;
				}
				case Gimmick::TYPE_DISAPPEAR_GROUND:
				{
					i += FindWord(word,&data[i],",\n\0");
					f32 x = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 y = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					u32 appear_frame = atoi(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					u32 disappear_frame = atoi(word);

					GimmickDisappearGround* gimmick = new GimmickDisappearGround();
					gimmick->Initialize();
					gimmick->__position(D3DXVECTOR2(x,y));
					gimmick->__appear_frame(appear_frame);
					gimmick->__disappear_frame(disappear_frame);
					gimmick_container_.push_back(gimmick);
					i += FindWord(word,&data[i],"\n\0");
					break;
				}
				case Gimmick::TYPE_MOVE_GROUND:
				{
					i += FindWord(word,&data[i],",\n\0");
					f32 x = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 y = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 end_x = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 end_y = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 speed = atof(word);

					GimmickMoveGround* gimmick = new GimmickMoveGround();
					gimmick->Initialize();
					gimmick->__position(D3DXVECTOR2(x,y));
					gimmick->__start_position(D3DXVECTOR2(x,y));
					gimmick->__end_position(D3DXVECTOR2(end_x,end_y));
					gimmick->__speed(speed);
					gimmick_container_.push_back(gimmick);
					i += FindWord(word,&data[i],"\n\0");
					break;
				}
				case Gimmick::TYPE_LENS:
				{
					i += FindWord(word,&data[i],",\n\0");
					f32 x = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 y = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					u32 vec = atoi(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 end_x = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 end_y = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 speed = atof(word);


					GimmickLens* gimmick = new GimmickLens();
					gimmick->Initialize();
					gimmick->__position(D3DXVECTOR2(x,y));
					gimmick->__shot_vec(vec);
					gimmick->__start_position(D3DXVECTOR2(x,y));
					gimmick->__end_position(D3DXVECTOR2(end_x,end_y));
					gimmick->__speed(speed);
					gimmick->__rotation_to_shot_vector();

					gimmick_container_.push_back(gimmick);
					i += FindWord(word,&data[i],"\n\0");
					break;
				}
				case Gimmick::TYPE_TUTORIAL_TEXT:
				{
					//みる
					i += FindWord(word,&data[i],",\n\0");
					//xを文字列からfloatに
					f32 x = atof(word);
					//次へ
					i++;
					//みる
					i += FindWord(word,&data[i],",\n\0");
					//yを文字列からfloatに
					f32 y = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					u32 massage = atoi(word);
					i++;
					//サイズ
					i += FindWord(word,&data[i],",\n\0");
					f32 sx = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 sy = atof(word);
					i++;


					GimmickTutorialText* gimmick = new GimmickTutorialText();
					gimmick->__type(massage);
					gimmick->Initialize();
					gimmick->__position(D3DXVECTOR2(x,y));
					gimmick->__size(D3DXVECTOR2(sx,sy));

					//無いと死ぬ
					gimmick_container_.push_back(gimmick);
					i += FindWord(word,&data[i],"\n\0");

					break;
				}
				case Gimmick::TYPE_MASSAGE:
				{
					//みる
					i += FindWord(word,&data[i],",\n\0");
					//xを文字列からfloatに
					f32 x = atof(word);
					//次へ
					i++;
					//みる
					i += FindWord(word,&data[i],",\n\0");
					//yを文字列からfloatに
					f32 y = atof(word);
					i++;
					//メッセージ番号
					i += FindWord(word,&data[i],",\n\0");
					u32 massage = atoi(word);
					i++;
					//サイズ
					i += FindWord(word,&data[i],",\n\0");
					f32 sx = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 sy = atof(word);
					i++;


					GimmickMassage* gimmick = new GimmickMassage();
					gimmick->__type(massage);
					gimmick->Initialize();
					gimmick->__position(D3DXVECTOR2(x,y));
					gimmick->__size(D3DXVECTOR2(sx,sy));

					//無いと死ぬ
					gimmick_container_.push_back(gimmick);
					i += FindWord(word,&data[i],"\n\0");

					break;
				}
				default:
				{
					i += FindWord(word,&data[i],"\n\0");
					break;
				}
			}
			count = 0;
		}
		else
		{
			word[count] = data[i];
			count++;
		}
	}

	SafeDeleteArray(data);

	for(auto it = gimmick_container_.begin();it != gimmick_container_.end();++it)
	{
		(*it)->__offset_position(stage_offset_->__position());
	}

	return true;
}

u32 NormalStage::FindWord(s8* dest,const s8* source,s8* words)
{
	u32 count = 0;
	u32 length = strlen(words);

	while(1)
	{
		for(u32 i = 0;i < length;++i)
		{
			if(source[count] == words[i])
			{
				dest[count] = '\0';
				return count;
			}
		}
		dest[count] = source[count];
		count++;
	}
}

//---------------------------------- EOF --------------------------------------
