#include "Player.h"
#include "Key.h"
#include<iostream>

Player::Player(b2World & world, std::string filename, float x, float y, float const SCALE, bool idle) :
	m_idle(idle)
{
	row = 0;
	if (!m_texture.loadFromFile("spriteSheet4.png"))
	{
		//std::cout << "Error Loading Block Texture!" << std::endl;
	}

	if (!m_batteryTexture.loadFromFile("ASSETS/IMAGES///Battery.png"))
	{

	}

	if (!m_batteryTexture1.loadFromFile("ASSETS/IMAGES///Battery1.png"))
	{

	}

	if (!m_batteryTexture2.loadFromFile("ASSETS/IMAGES///Battery2.png"))
	{

	}

	if (!m_batteryTexture3.loadFromFile("ASSETS/IMAGES///Battery3.png"))
	{

	}

	if (!m_batteryTexture4.loadFromFile("ASSETS/IMAGES///Battery4.png"))
	{

	}

	if (!m_batteryTexture5.loadFromFile("ASSETS/IMAGES///Battery5.png"))
	{

	}

	//if (!m_keyIconT.loadFromFile("ASSETS/IMAGES///keyPickup.png"))
	//{

	//}


	if (!m_shader.loadFromFile("ASSETS/SHADERS///player.frag", sf::Shader::Fragment))
	{
		std::cout << "player shader failed to load" << std::endl;         //load shader
	}
	if (!m_blank.loadFromFile("ASSETS/IMAGES///Blank.png"))
	{

	}

	if (!m_Idle.loadFromFile("Idle2.png"))
	{

	}

	if (!m_testT.loadFromFile("ASSETS/IMAGES/footballl2.png"))
	{

	}

	if (!m_buffer2.loadFromFile("ASSETS\\SOUNDS\\this.wav"))
	{
	}
	m_runSound.setBuffer(m_buffer2);

	if (!m_buffer3.loadFromFile("ASSETS\\SOUNDS\\jump.wav"))
	{
	}
	m_jumpSound.setBuffer(m_buffer3);

	running = new Animation(&m_texture, sf::Vector2u(22, 1), 0.05);
	idleA = new Animation(&m_Idle, sf::Vector2u(22, 1), 0.05);

	m_bodyDef.position = b2Vec2(x / SCALE, y / SCALE);
	m_bodyDef.type = b2_dynamicBody;
	m_body = world.CreateBody(&m_bodyDef);

	m_bodyDef2.position = b2Vec2(x / SCALE, y / SCALE);
	m_bodyDef2.type = b2_dynamicBody;
	m_body2 = world.CreateBody(&m_bodyDef);
	
	m_shape.m_p.Set((64.f) / SCALE, (64.f) / SCALE);
	m_shape.m_radius = (27.f) / SCALE;
	//m_headCollider.m_p.Set((64.f) / SCALE, (64.f) / SCALE);
	//m_headCollider.m_radius = (25.f) / SCALE;

	m_fixtureDef.density = 1.f;
	m_fixtureDef.friction = 0.0f;
	m_fixtureDef.restitution = 0.0f;
	m_fixtureDef.shape = &m_shape;
	m_body->CreateFixture(&m_fixtureDef);
	m_body->SetFixedRotation(true);
	//m_idle = true;
//	m_fixtureDef2.density = 0.f;
//	m_fixtureDef2.friction = 0.8f;
//	m_fixtureDef2.restitution = 0.0f;
//	m_fixtureDef2.shape = &m_headCollider;
//	m_body2->CreateFixture(&m_fixtureDef2);
	//m_body2->SetFixedRotation(true);

	if (m_idle == false)
	{
		m_sprite.setTexture(m_texture);
		m_sprite.setOrigin(112 / SCALE, 112 / SCALE);
		m_sprite.setPosition(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE);
		m_sprite.setRotation(180 / b2_pi * m_body->GetAngle());
		m_shape.m_p.Set((64.f) / SCALE, (64.f) / SCALE);
	//	m_headCollider.m_p.Set((64.f) / SCALE, (64.f) / SCALE);
	}
	else
	{
		m_sprite.setTexture(m_Idle);
		m_sprite.setOrigin(112 / SCALE, 112 / SCALE);
		m_sprite.setPosition(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE);
		m_sprite.setRotation(180 / b2_pi * m_body->GetAngle());
		m_shape.m_p.Set((64.f) / SCALE, (64.f) / SCALE);
	//	m_headCollider.m_p.Set((64.f) / SCALE, (64.f) / SCALE);
	}

	m_shader.setUniform("resolution", sf::Vector2f(1920, 1080));

	m_shader.setUniform("battery", m_battery);

	m_shaderSprite.setTexture(m_blank);
	m_shaderSprite.setPosition(0, 0);
	m_shaderSprite.setOrigin(m_blank.getSize().x / 2, m_blank.getSize().y / 2);
	m_shaderSprite.setScale(8.5, 7.5);

	//m_testSprite.setTexture(m_testT);
//	m_testSprite.setPosition(0, 0);
//	m_testSprite.setOrigin(m_blank.getSize().x / 2, m_blank.getSize().y / 2);
//	m_testSprite.setScale(8.5, 7.5);

	m_batterySprite.setTexture(m_batteryTexture);
	m_batterySprite.setPosition(m_sprite.getPosition().x - 550, m_sprite.getPosition().y - 350);
	m_batterySprite.setScale(2, 1);

	m_dust = new Particles(m_sprite.getPosition());

	///m_keyIcon.setTexture(m_keyIconT);
//	m_keyIcon.setPosition(m_sprite.getPosition().x + 550, m_sprite.getPosition().y + 350);
	key = std::make_unique<Key>(world, x,y, 2);

	///m_keyIcon.setTexture(m_keyIconT);
//	m_keyIcon.setPosition(m_sprite.getPosition().x + 550, m_sprite.getPosition().y + 350);
	key = std::make_unique<Key>(world, x,y, 2);

}




Player::~Player()
{

}


void Player::Update(float deltaTime, sf::View & v)
{

	m_batterySprite.setPosition(m_sprite.getPosition().x - 550, m_sprite.getPosition().y - 350);

	/*if (m_runningB == true)
	{
		m_runSound.play();
		m_runningB = false;
	}*/

//	m_keyIcon.setPosition(m_sprite.getPosition().x + 10, m_sprite.getPosition().y + 30);


	sf::Vector2f movement(0.0f, 0.0f);
	m_xbox.update();
	m_sprite.setPosition(m_body->GetPosition().x * 30+32, m_body->GetPosition().y * 30+32);
	m_shaderSprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y);
	//m_testSprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y);
	v.setCenter(m_sprite.getPosition().x, m_sprite.getPosition().y);

	

	direction.y = -m_xbox.m_currentState.RightThumbStick.x;
	direction.x = m_xbox.m_currentState.RightThumbStick.y;
	m_shader.setUniform("direction", direction);

	m_shader.setUniform("battery", m_battery);
	m_battery -= m_batterySpeed;

	if (m_battery > -499)
	{
		m_batterySpeed = 0.5;
	}

	if (m_battery > -99)
	{
		m_batterySprite.setTexture(m_batteryTexture);
	}
	else if (m_battery == -100)
	{
		m_batterySprite.setTexture(m_batteryTexture5);
	}
	else if (m_battery == -200)
	{
		m_batterySprite.setTexture(m_batteryTexture4);
	}
	else if (m_battery == -300)
	{
		m_batterySprite.setTexture(m_batteryTexture3);
	}
	else if (m_battery == -499)
	{
		m_batterySprite.setTexture(m_batteryTexture2);
	}
	else if (m_battery == -700)
	{
		m_batterySpeed = 10;
		m_batterySprite.setTexture(m_batteryTexture1);
		m_battery = -500;
	}

		//std::cout << m_body->GetLinearVelocity().y << std::endl;
		m_body->SetLinearVelocity(b2Vec2(0, m_body->GetLinearVelocity().y));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && jump == false || (m_xbox.m_currentState.A && m_xbox.m_previousState.A != m_xbox.m_currentState.A) && jump == false)
		{
			m_body->ApplyForceToCenter(b2Vec2(0, -3500),0);
			jump = true;

			m_clock.restart();
		}


	if (m_clock.getElapsedTime().asSeconds() > wait)
	{
		jump = false;
	}

//	jump = false;


		

	//if (jumpoften != 1)
	//{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || m_xbox.m_currentState.LeftThumbStick.x < -75)
		{
			m_dust->update(sf::Vector2f(m_sprite.getPosition().x + 50, m_sprite.getPosition().y), true);
			m_body->SetLinearVelocity(b2Vec2(-15, m_body->GetLinearVelocity().y));
			v.move(-15, 0);
		//	m_runSound.setLoop(true);
			if (m_runSound.getStatus() != m_runSound.Playing)
			{
				m_runSound.play();
				m_dust->active = true;
			}

			if (jump == true && m_body->GetPosition().x <= 3.9)
			{
				m_body->SetLinearVelocity(b2Vec2(-15, 15));
		
				if (m_runSound.getStatus() != m_runSound.Stopped)
				{
					m_runSound.stop();
					m_dust->active = false;
				}

				/*if (m_jumpSound.getStatus() != m_jumpSound.Playing)
				{
					m_jumpSound.play();
				}*/
				
			}
			if (jump == true && m_body->GetPosition().x >= 0)
			{

				if (m_runSound.getStatus() != m_runSound.Stopped)
				{
					m_dust->active = false;
					m_runSound.stop();
				//	m_jumpSound.play();
				}
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || m_xbox.m_currentState.LeftThumbStick.x > 75)
		{
			m_dust->update(m_sprite.getPosition(), false);
			m_body->SetLinearVelocity(b2Vec2(15, m_body->GetLinearVelocity().y));
			v.move(15, 0);

			if (m_runSound.getStatus() != m_runSound.Playing)
			{
				m_runSound.play();
				m_dust->active = true;
			}
			
			if (jump == true && m_body->GetPosition().x <= 3.9)
			{
				m_body->SetLinearVelocity(b2Vec2(15, 15));
			
				if (m_runSound.getStatus() != m_runSound.Stopped)
				{
					m_runSound.stop();
					m_dust->active = false;
				}
			}

			if (jump == true && m_body->GetPosition().x >= 0)
			{

				if (m_runSound.getStatus() != m_runSound.Stopped)
				{
					m_runSound.stop();
					m_dust->active = false;
				}
			}

		}
		//jumpoften++;
	//}
	else
	{
		jumpoften = 0;
		m_runningB = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || m_xbox.m_currentState.LeftThumbStick.y > 90)
	{

	}
		
	/*if ( key->collected == true && m_xbox.m_currentState.A)
	{
		std::cout << "Playing Audio" << std::endl;
		door->m_doorSound.play();
	}
	*/
	if (m_body->GetLinearVelocity().x == 0)
	{
		//row = 0;
	}
	else
	{
		row = 0;
		if (m_body->GetLinearVelocity().x > 0.0f)
		{
			faceRight = true;
		}
		else
		{
			faceRight = false;
		}
	}
	if (m_body->GetLinearVelocity().x == 0)
	{
		if (m_runSound.getStatus() != m_runSound.Stopped)
		{
			m_runSound.stop();
			m_dust->active = false;
		}
		m_idle = true;
		row = 0;
			//m_sprite.setTexture(m_Idle);
	//	std::cout << "Vel x = " << m_body->GetLinearVelocity().x << std::endl;
	}
	else
	{
		m_idle = false;
	//	std::cout << "Vel x = " << m_body->GetLinearVelocity().x << std::endl;
	//	m_sprite.setTexture(m_texture);
	}

	if (m_idle) {
		m_sprite.setTexture(m_Idle);
		idleA->update(row, deltaTime, faceRight);
		m_sprite.setTextureRect(idleA->uvRect);
	}
	else
	{
		m_sprite.setTexture(m_texture);
		running->update(row, deltaTime, faceRight);
		m_sprite.setTextureRect(running->uvRect);
	}

	if (key->collected == true)
	{
		keyDraw = true;
	}
	
}

void Player::Draw(sf::RenderWindow& window)
{
	
	
	window.draw(m_sprite);
	if(keyDraw == true)
	{
		window.draw(m_keyIcon);
	}
	window.draw(m_shaderSprite, &m_shader);
	window.draw(m_batterySprite);
	m_dust->render(window);
	//window.draw(m_testSprite);
}

sf::Vector2f Player::getPosition()
{
	return sf::Vector2f (m_body->GetPosition().x , m_body->GetPosition().y);
}
