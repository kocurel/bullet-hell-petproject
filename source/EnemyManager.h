/// @file EnemyManager.h
/// @brief declares the EnemyManager manager class responsible
/// for storing and management of Enemy class objects
#pragma once
#include <vector>
#include <memory>
#include <functional>
#include "IEnemyManager.h"

//forward declarations
namespace sf {
	class RenderWindow;
}
class Enemy;
class Projectile;
class IEventManager;
class Player;
class ProjectileManager;
class PickupManager;

/// @brief Enemy manager class.
/// Keeps all enemies inside a vector of unique pointers
/// Is responsible for calling Enemy::process(Player&), Enemy::render(sf::RenderWindow&), 
/// receiving new enemies and cleaning up the disabled enemies.
/// Has exclusive ownership over the stored objects
/// @sa Enemy
class EnemyManager : public IEnemyManager {
private:
	/// @brief A reference to the interface of EventManager.
	/// It's used to call endWave(), whenever there are no more active enemies.
	IEventManager& wave_controller_;
	
	/// @brief A vector of unique pointers to Enemy class objects.
	/// Main storage object of the EnemyManager class.
	std::vector<std::unique_ptr<Enemy>> enemies_;
	
	/// @brief A counter used to count frames between cleanupEnemies()
	/// checking all the enemies and removing the disabled ones.
	/// @sa EnemyManager::cleanupEnemies
	int cleanup_counter_ = 360;
	
	/// @brief A counter used to count frames between checkWave()
	/// verifying and notifying the wave controller if there aren't any active enemies.
	/// @sa EnemyManager::checkWave
	int wave_counter_ = 30;
	
	/// @brief A lambda expression to check if enemy is disabled
	const std::function<bool(const std::unique_ptr<Enemy>&)> is_enemy_disabled;
	
	/// @brief A lambda expression to check if enemy is not disabled 
	const std::function<bool(const std::unique_ptr<Enemy>&)> is_enemy_not_disabled;
	
	/// @brief A lambda expression to check if projectile is disabled 
	const std::function<bool(const std::unique_ptr<Projectile>&)> is_projectile_not_disabled;
	
	/// @brief Decrements the cleanup_counter_, if it reaches 0 the method 
	/// will check all enemies and remove the disabled ones.
	/// @sa EnemyManager::cleanup_counter_
	void cleanupEnemies();

	/// @brief Decrements the wave_counter_, if it reaches 0 the method will
	/// check if there are any active (non-disabled) enemies. If there aren't
	/// any the method will call IEventManager::endWave().
	/// @sa IEventManager::endWave, EventManager, EnemyManager::wave_counter_
	void checkWave();
public:
	/// @brief Disabled copy constructor
	EnemyManager(EnemyManager&) = delete;
	
	/// @brief Disabled copy assignment
	EnemyManager& operator=(EnemyManager&) = delete;

	/// @brief The class constructor.
	/// @param wave_controller - Reference to the
	/// IEventManager interface of EventManager to let
	/// EnemyManager call IEventManager::endWave().
	/// @sa IEventManager, EnemyManager::checkWave
	explicit EnemyManager(IEventManager& wave_controller);

	/// @brief Clears the enemies_ vector.
	/// @details To be called when starting a new game.
	/// @sa EnemyManager::enemies_
	void clear() override;

	/// @brief Main process function. Is to be called each frame
	/// by the game controller. It is resposible for calling
	/// cleanupEnemies(),checkWave() and calling Enemy::process(Player&)
	/// for each non-disabled enemy and checking collisions with player projectiles.
	/// @param player - a reference to the Player object, necessary to pass as a parammeter to Enemy::process()
	/// @param projectiles - a reference to the ProjectileManager, necessary to check for collisions.
	/// @param pickups - a reference to the PickupManager, necessary for enemies to create pickups on destruction.
	/// @sa EnemyManager::cleanupEnemies, EnemyManager::checkWave, Enemy::process, CollisionCircle::checkCollision
	void process(Player& player, IProjectileManager& projectiles, IPickupManager& pickups) override;

	/// @brief Moves a unique pointer passed as parameter to the enemies_ vector.
	/// Once called, the EnemyManager class becomes the owner of the enemy object.
	/// @param enemy - a unique pointer to the new enemy object.
	/// @sa EnemyManager::enemies_
	void createEnemy(std::unique_ptr<Enemy>&& enemy) override;

	/// @brief Calls render(sf::RenderWindow&) of all the non-disabled enemies.
	/// @param window - a reference to the RenderWindow, necessary to pass as a parameter to SpriteOwner::render(RenderWindow&)
	/// @sa SpriteOwner::render
	void render(sf::RenderWindow& window) const override;

	const std::vector<std::unique_ptr<Enemy>>& getEnemies() const override;

	/// @brief EnemyManager destructor
	~EnemyManager();
};