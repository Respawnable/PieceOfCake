
void PlayEndSound()
{
	nVolume = 4;
	PlaySoundFile("stopped.rso");
	while (bSoundActive)
	{};
	wait1Msec(1000);
	PlaySound(soundFastUpwardTones);
	while (bSoundActive)
	{};
	wait1Msec(2000);

	while (true)
	{
		PlaySoundFile("3.rso");
		PlaySoundFile("7.rso");
		PlaySoundFile("6.rso");
		PlaySoundFile("3.rso");
		while (bSoundActive)
		{};
		wait1Msec(1000);
	}
}

task main()
{
	PlayEndSound();
}
