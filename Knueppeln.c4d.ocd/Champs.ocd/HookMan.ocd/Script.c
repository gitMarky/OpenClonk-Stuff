/**
	FireMan
	

	@author 
*/

#include Man

local Description = "$Description$";
local Name = "$Name$";

local Special1Spell = Hook;
local Special2Spell = ExplosiveHook;
local Special3Spell = SawBlade;

local Special1Cooldown = 30;
local Special3Cooldown = 400;

func Special1(object clonk, int x, int y, bool released, bool mouseclick, bool abletocast, bool cooldown)
{
	if(clonk.currHook && !released && abletocast)
	{
		clonk.currHook->Trigger();
		return 1;
	}

	if(!released && !mouseclick && abletocast && !cooldown)
	{
		clonk.currHook = clonk->LaunchSpell(Special1Spell, x, y, 0, 0);
		if(clonk.currHook)
		{
			return 1;
		}
	}
	return 0;
}

func Special2(object clonk, int x, int y, bool released, bool mouseclick, bool abletocast, bool cooldown)
{
	if(!released && !mouseclick && abletocast && !cooldown)
	{
		if(clonk->LaunchSpell(Special2Spell, x, y, 0, 0))
			return 1;
	}
	return 0;
}

func Special3(object clonk, int x, int y, bool released, bool mouseclick, bool abletocast, bool cooldown)
{
	if(!released && !mouseclick && abletocast && !cooldown)
	{
		if(clonk->LaunchSpell(Special3Spell, x, y, 0, 0))
			return 1;
	}
	return 0;
}

func JumpEffect(object clonk, dir)
{
	var from;
	var to;

	if (dir == "Up")
	{
		from = 50; 
		to = 130;
	}
	if (dir == "Left")
	{
		from = -30; 
		to = 50;
	}
	if (dir == "Right")
	{
		from = 130; 
		to = 210;
	}
	if (dir == "Down")
	{
		from = 230; 
		to = 310;
	}

	Sound("hookjump", false, 30);

	for(var i = from; i < to; i+=5)
	{
		var r = 10;
		var x = clonk->GetX() + Cos(i, r);
		var y = clonk->GetY() + Sin(i, r);
		
		var angle = Angle(0,0,Cos(i, r),Sin(i, r));
		
		var trailparticles =
		{
			//Prototype = Particles_ElectroSpark2(),
			Size = PV_Linear(10,0),
			Rotation = angle,
			R = 150,
			G = 150,
			B = 150,
			OnCollision = PC_Bounce(),
		};
	
		CreateParticle("Shockwave", x, y, Cos(i, r + RandomX(-1,1)), Sin(i, r + RandomX(-1, 1)), 10, trailparticles);
	}
}

func BlockEffect(object clonk, range)
{
	for(var i = 0; i < 360; i+=10)
	{
		var r = range;
		var x = clonk->GetX() + Cos(i, r);
		var y = clonk->GetY() + Sin(i, r);
		
		var angle = Angle(0,0,Cos(i, r),Sin(i, r)) + 90;
		
		var trailparticles =
		{
			Size = PV_Linear(15,0),
			Rotation = angle,
			R = 150,
			G = 150,
			B = 150,
		};
	
		CreateParticle("Shockwave", x, y, 0, 0, 10, trailparticles);
	}
	
}
