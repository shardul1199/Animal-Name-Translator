#pragma once

using namespace System;
public ref class Paths
{
private: 
	String ^name;
	String^ imagePath;
	String^ audioPath;
	String^ animalSounds;
	String^ description;
public:
	void setName(String ^nam)
	{
		name = nam;
	}
	void setImagePath(String^ path)
	{
		imagePath = path;
	}
	void setDescription(String^ text)
	{
		description = text;
	}
	void setAudioPath(String^ path)
	{
		audioPath = path;
	}
	void setAnimalSounds(String^ path)
	{
		animalSounds = path;
	}
	String^ getImagePath()
	{
		return imagePath;
	}
	String^ getDescription()
	{
		return description;
	}
	String^ getAudioPath()
	{
		return audioPath;
	}
	String^ getAnimalSounds()
	{
		return animalSounds;
	}
	String^ getName()
	{
		return name;
	}
};
