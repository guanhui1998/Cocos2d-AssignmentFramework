#include "EnemyProjectileManager.h"

EnemyProjectileManager::EnemyProjectileManager()
{
	CCLOG("EnemyProjectileManager singleton created");
}

EnemyProjectileManager::~EnemyProjectileManager()
{
}

void EnemyProjectileManager::Init()
{
	CCLOG("EnemyProjectileManager Init");
}

void EnemyProjectileManager::Update(float dt)
{
	for (vector<EnemyBaseProjectile*>::iterator it = ProjectileList.begin(); it != ProjectileList.end();)
	{
		(*it)->Update(dt);
		if ((*it)->destroy)
		{
			EnemyBaseProjectile* t = *it;
			it = ProjectileList.erase(it);
			t->release();
			delete t;
		}
		else
		{
			it++;
		}
	}



}

void EnemyProjectileManager::CreateEnemyProjectile(string sprite_filename, Vec2 Direction_vector, Vec2 position)
{
	EnemyBaseProjectile* temp = new EnemyBaseProjectile();
	temp->Init(sprite_filename, Direction_vector, position);
	ProjectileList.push_back(temp);
}
void EnemyProjectileManager::CreateEnemyProjectile(string sprite_filename, Vec2 Direction_vector, Vec2 position, float lifetime)
{
	EnemyBaseProjectile* temp = new EnemyBaseProjectile();
	temp->Init(sprite_filename, Direction_vector, position, lifetime);
	ProjectileList.push_back(temp);
}

void EnemyProjectileManager::AddEnemyProjectile(EnemyBaseProjectile* projectile)
{
	ProjectileList.push_back(projectile);
}

int EnemyProjectileManager::get_Number_of_Projectiles()
{
	return ProjectileList.size();
}

void EnemyProjectileManager::Release()
{
	while (ProjectileList.size() > 0)
	{
		EnemyBaseProjectile* projectile = ProjectileList.back();
		projectile->release();
		ProjectileList.pop_back();
		delete projectile;
	}
}