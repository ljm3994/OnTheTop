#include "stdafx.h"
#include "SoundManager.h"


SoundManager::SoundManager()
	:m_system(nullptr)
{
	//사운드 시스템 생성
	System_Create(&m_system);

	//사운드 채널수 생성
	m_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);
	
	
}


SoundManager::~SoundManager()
{
	arrSoundIter iter = m_totalSound.begin();
	for (iter; iter != m_totalSound.end(); ++iter)
	{
		bool isPlaying;
		iter->second.m_channel->isPlaying(&isPlaying);
		if (isPlaying)
		{
			iter->second.m_channel->stop();
		}
		iter->second.m_sound->release();
	}

	//시스템 닫기
	if (m_system != nullptr)
	{
		m_system->release();
		m_system->close();
	}
	//맵 비우기
	m_totalSound.clear();
}

void SoundManager::addSound(string keyName, string soundName, bool loop)
{
	SoundInfo m_sound;	
	if (loop)
	{
		m_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, nullptr, &m_sound.m_sound);

	}
	else
	{
		m_system->createStream(soundName.c_str(), FMOD_DEFAULT, nullptr, &m_sound.m_sound);
	}

	//맵에 사운드를 키값과 함께 담아준다.
	m_totalSound.insert(make_pair(keyName, m_sound));
}

void SoundManager::play(string keyName, float volume)
{
	bool isPlaying;
	arrSoundIter iter = m_totalSound.begin();
	for (iter; iter != m_totalSound.end(); ++iter)
	{
		if (keyName == iter->first)
		{
			iter->second.m_channel->isPlaying(&isPlaying);
			if (isPlaying) return;
			//사운드 플레이
			
			m_system->playSound(FMOD_CHANNEL_FREE, iter->second.m_sound, false, &iter->second.m_channel);
			//볼륨셋팅
			iter->second.m_channel->setVolume(volume);
		}
	}
}

void SoundManager::stop(string keyName)
{
	arrSoundIter iter = m_totalSound.begin();
	for (iter; iter != m_totalSound.end(); ++iter)
	{
		if (keyName == iter->first)
		{
			bool isPlaying;
			iter->second.m_channel->isPlaying(&isPlaying);
			if (isPlaying)
			{
				iter->second.m_channel->stop();
			}
			break;
		}
	}
}

void SoundManager::pause(string keyName)
{
	arrSoundIter iter = m_totalSound.begin();
	for (iter; iter != m_totalSound.end(); ++iter)
	{
		if (keyName == iter->first)
		{
			iter->second.m_channel->setPaused(true);
			break;
		}
	}
}

void SoundManager::resume(string keyName)
{
	arrSoundIter iter = m_totalSound.begin();
	for (iter; iter != m_totalSound.end(); ++iter)
	{
		if (keyName == iter->first)
		{
			iter->second.m_channel->setPaused(false);
			break;
		}
	}
}

bool SoundManager::isPlaySound(string keyName)
{
	bool isPlay = false;
	arrSoundIter iter = m_totalSound.begin();
	for (iter; iter != m_totalSound.end(); ++iter)
	{
		if (keyName == iter->first)
		{
			iter->second.m_channel->isPlaying(&isPlay);
			break;
		}
	}
	return isPlay;
}

bool SoundManager::isPauseSound(string keyName)
{
	return false; bool isPause;
	int count = 0;
	arrSoundIter iter = m_totalSound.begin();
	for (iter; iter != m_totalSound.end(); ++iter)
	{
		if (keyName == iter->first)
		{
			iter->second.m_channel->getPaused(&isPause);
			break;
		}
	}
	return isPause;
}
void SoundManager::Update()
{
	/*
	사운드 시스템을 계속 업데이트 해줘야 볼륨이 바뀌거나
	재생이 끝난 사운드를 채널에서 빼내는 등 다양한 작업을 자동으로 해준다.
	*/
	//메인게임에서 사운드 매니져를 업데이트 해준다.
	m_system->update();
}

UINT SoundManager::GetPosition(string keyName)
{
	bool isPlaying;
	UINT Position = 0;
	arrSoundIter iter = m_totalSound.begin();
	for (iter; iter != m_totalSound.end(); ++iter)
	{
		if (keyName == iter->first)
		{
			//사운드 플레이
			iter->second.m_channel->getPosition(&Position, FMOD_TIMEUNIT_MS);
		}
	}

	return Position;
}
