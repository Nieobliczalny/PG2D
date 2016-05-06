//For educational use only
//NOT TO BE USED IN COMMERCIAL OR SCHOOL PROJECTS

#pragma once

#include <wrl.h>


//#include "..\Common\DirectXHelper.h"	// For ThrowIfaFailed and ReadDataAsync

#include <Content\AnimatedTexture.h>
#include <SpriteBatch.h>

#include <DirectXMath.h>
#include <SimpleMath.h>

#include "..\Common\SpriteSheet.hpp"


class Player
{
public:
	Player(std::shared_ptr<SpriteSheet> playerSpriteSheet) : framesOfAnimation(4), framesToBeShownPerSecond(4), totalElapsed(0)
	{
		position = DirectX::XMFLOAT2(300, 512);
		
		//Instantiate animation here
		texture = playerSpriteSheet->Find(L"Mech12");
		addPart(playerSpriteSheet->Find(L"Mech12_arm_l"), DirectX::XMFLOAT2(2, 0));
		addPart(playerSpriteSheet->Find(L"Mech12_arm_r"), DirectX::XMFLOAT2(57, 0));
		addPart(playerSpriteSheet->Find(L"Mech12_leg_l"), DirectX::XMFLOAT2(10, 10));
		addPart(playerSpriteSheet->Find(L"Mech12_leg_r"), DirectX::XMFLOAT2(53, 10));
		addPart(playerSpriteSheet->Find(L"Mech12_torso"), DirectX::XMFLOAT2(6, 6));
		addPart(playerSpriteSheet->Find(L"Mech12_shoulder"), DirectX::XMFLOAT2(0, 3));
		addPart(playerSpriteSheet->Find(L"Mech12_head"), DirectX::XMFLOAT2(30, 8));

		spriteSheet = playerSpriteSheet;
		float rotation = 0.f;
		float scale = 3.f;
		//animation.reset(new AnimatedTexture(DirectX::XMFLOAT2(0.f, 0.f), rotation, scale, 0.5f));
		//animation->Load(texture.Get(), framesOfAnimation, framesToBeShownPerSecond);
		width = textureWidth = texture->size.x;//animation->getFrameWidth();
		height = textureHeight = texture->size.y;//animation->getFrameHeight();

		rectangle.X = position.x;
		rectangle.Y = position.y;
		rectangle.Height = height;
		rectangle.Width = width;
		
	}

	void setPosition(DirectX::XMFLOAT2 newPosition)
	{
		//set the position
		position = newPosition;
		updateBoundingRect();
	}

	void setPosition(float posX, float posY)
	{
		position.x = posX;
		position.y = posY;
		updateBoundingRect();
	}

	DirectX::XMFLOAT2 getPosition()
	{
		return position; 
	}

	void Update(float elapsed)
	{
		totalElapsed += elapsed;
		float splitFrame = totalElapsed - ((int)totalElapsed / 4) * 4;
		int frame = floor(splitFrame * 24 / 4);
		if (frame > 12)
		{
			frame = 24 - frame;
		}
		parts.at(2).position.y = 10 + frame;
		parts.at(3).position.y = 10 + frame;
		//update the animation of the player
		//animation->Update(elapsed);
	}

	void Draw(DirectX::SpriteBatch* batch)
	{
		//animation->Draw(batch, position);
		//spriteSheet->Draw(batch, *texture, position);
		for (auto& part : parts)
		{
			DirectX::XMFLOAT2 position(part.position.x + this->position.x + part.frame->origin.x, part.position.y + this->position.y + part.frame->origin.y);
			spriteSheet->Draw(batch, *(part.frame), position);
		}
	}


public:
	Windows::Foundation::Rect							rectangle;

private:
	void updateBoundingRect()
	{
		//TODO: proper updating when rotating player object
		rectangle.X = position.x - texture->origin.x;
		rectangle.Y = position.y - texture->origin.y;
		rectangle.Height = height;
		rectangle.Width = width;
	}

	Windows::Foundation::Rect getBoundingRect()
	{
		return rectangle;
	}
	void addPart(const SpriteSheet::SpriteFrame* frame, DirectX::XMFLOAT2 position)
	{
		PartData part;
		part.frame = frame;
		part.position = position;
		parts.push_back(part);
	}

	struct PartData
	{
		const SpriteSheet::SpriteFrame* frame;
		DirectX::XMFLOAT2 position;
	};

	DirectX::XMFLOAT2									position;

	int													width;
	int													height;
	int													textureWidth;
	int													textureHeight;
	int													framesOfAnimation;
	int													framesToBeShownPerSecond;

	//Texture and animation
	const SpriteSheet::SpriteFrame*						texture;
	std::vector<PartData>								parts;
	//std::unique_ptr<AnimatedTexture>					animation;
	std::shared_ptr<SpriteSheet>						spriteSheet;
	float												totalElapsed;

};