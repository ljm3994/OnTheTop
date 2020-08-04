#include "stdafx.h"
#include "SoundManager.h"


SoundManager::SoundManager()
	:m_system(nullptr)
{
	//���� �ý��� ����
	System_Create(&m_system);

	//���� ä�μ� ����
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

	//�ý��� �ݱ�
	if (m_system != nullptr)
	{
		m_system->release();
		m_system->close();
	}
	//�� ����
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

	//�ʿ� ���带 Ű���� �Բ� ����ش�.
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
			//���� �÷���
			
			m_system->playSound(FMOD_CHANNEL_FREE, iter->second.m_sound, false, &iter->second.m_channel);
			//��������
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
	���� �ý����� ��� ������Ʈ ����� ������ �ٲ�ų�
	����� ���� ���带 ä�ο��� ������ �� �پ��� �۾��� �ڵ����� ���ش�.
	*/
	//���ΰ��ӿ��� ���� �Ŵ����� ������Ʈ ���ش�.
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
			//���� �÷���
			iter->second.m_channel->getPosition(&Position, FMOD_TIMEUNIT_MS);
		}
	}

	return Position;
}
