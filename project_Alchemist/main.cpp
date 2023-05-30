#include <map>
#include <iostream>
#include <random>
#include <utility>
// class Aventurier{
//     public:
//     int p
// }

class merchant{
    public:
    int _gold;
    std::map<std::string, int> _inventory;

    merchant(){
        _gold = 100;
        _inventory["Herbe medicinale"] = 10;
        _inventory["Noyau de monstre"] = 10;
        _inventory["Couille de gobelin"] = 2;
        _inventory["Potion de soin inferieur"] = 1;
        _inventory["Potion de force"] = 0; 
        _inventory["Potion de soin superieur"] = 0;
    }

    void displayInventory() {
        std::cout << "Voici votre inventaire" << std::endl;
        std::cout << "Vous avez " << _gold << " golds" << std::endl;
        for (auto it = _inventory.begin(); it != _inventory.end(); it++) {
            if (it->second > 0)
                std::cout << "  -"<<it->first << " : " << it->second << std::endl;
        }
    }
    void displayPotion() {
        std::cout << "Voici vos potions" << std::endl;
        for (auto it = _inventory.begin(); it != _inventory.end(); it++) {
            if (it->first.find("Potion") != std::string::npos)
                std::cout << it->first << " : " << it->second << std::endl;
        }
    }
};

class Game {
    public:
    merchant _merchant;
    Game(){};
    void init() {
        system("clear");
        std::cout << "Vous etes un alchimiste vendant des potions" << std::endl;
    }

    void recruter() {
        while (1){
            std::cout << "Quel quete poster ?" << std::endl;
            std::cout << "1. Cueillette de plantes : 10 golds : 95 %" << std::endl;
            std::cout << "2. Recuperation de noyau de monstres : 30 golds : 70 %" << std::endl;
            std::cout << "3. Ablation de gonades gobelines : 50 golds : 55 %" << std::endl;
            std::cout << "4. Retour" << std::endl;
            std::cout << "Si cela echoue vous serez rembourse a la moitie" << std::endl;
            int prix;
            int chance;
            std::pair<std::string, int> reward;
            int choice;
            std::cin >> choice;
            system("clear");
            switch (choice) {
                case 1:
                    std::cout << "Vous avez poste une quete de cueillette de plantes" << std::endl;
                    prix = 10;
                    chance = 95;
                    reward = std::make_pair("Herbe medicinale", 10);
                    break;
                case 2:
                    std::cout << "Vous avez poste une quete de recuperation de noyau de monstres" << std::endl;
                    prix = 30;
                    chance = 70;
                    reward = std::make_pair("Noyau de monstre", 6);
                    break;
                case 3:
                    std::cout << "Vous avez poste une quete d'ablation de gonades gobelines" << std::endl;
                    prix = 50;
                    chance = 55;
                    reward = std::make_pair("Couille de gobelin", (rand() % 2) + 1);
                    break;
                case 4:
                    return;
            }
            if (_merchant._gold < prix){
                std::cout << "Vous n'avez pas assez d'argent" << std::endl;
            }
            else
            {
                int rando = std::rand() % 100;
                if (rando > chance){
                    std::cout << "Votre quete a echoue" << std::endl;
                    _merchant._gold -= prix / 2;
                } else {
                    std::cout << "Votre quete a reussi" << std::endl;
                    std::cout << "Vous avez recu " << reward.second << " " << reward.first << std::endl;
                    _merchant._gold -= prix;
                    _merchant._inventory[reward.first] += reward.second;
                }
            }
            _merchant.displayInventory();
        }
    }

    void creerPotion(){
        while (1){
            std::cout << "Quel potion voulez vous creer ?" << std::endl;
            std::cout << "1. Potion de soin inferieur : 3 herbe medicinale/1 noyau de monstre" << std::endl;
            std::cout << "2. Potion de force : 2 noyau de monstre/1 couille de gobelin" << std::endl;
            std::cout << "3. Potion de soin superieur : 3 herbe medicinale/2 couille de gobelin" << std::endl;
            std::cout << "4. Retour" << std::endl;
            int choice;
            std::cin >> choice;
            system("clear");
            switch (choice) {
                case 1:
                    if (_merchant._inventory["Herbe medicinale"] < 3 || _merchant._inventory["Noyau de monstre"] < 1){
                        std::cout << "Vous n'avez pas assez d'ingredient" << std::endl;
                        break;
                    }
                    _merchant._inventory["Herbe medicinale"] -= 3;
                    _merchant._inventory["Noyau de monstre"] -= 1;
                    _merchant._inventory["Potion de soin inferieur"] += 1;
                    break;
                case 2:
                    if (_merchant._inventory["Noyau de monstre"] < 2 || _merchant._inventory["Couille de gobelin"] < 1){
                            std::cout << "Vous n'avez pas assez d'ingredient" << std::endl;
                            break;
                    }
                    _merchant._inventory["Noyau de monstre"] -= 2;
                    _merchant._inventory["Couille de gobelin"] -= 1;
                    _merchant._inventory["Potion de force"] += 1;
                    break;
                case 3:
                    if (_merchant._inventory["Herbe medicinale"] < 3 || _merchant._inventory["Couille de gobelin"] < 2){
                            std::cout << "Vous n'avez pas assez d'ingredient" << std::endl;
                            break;
                    }
                    _merchant._inventory["Herbe medicinale"] -= 3;
                    _merchant._inventory["Couille de gobelin"] -= 2;
                    _merchant._inventory["Potion de soin superieur"] += 1;
                    break;
                case 4:
                    return;
            }
            _merchant.displayInventory();
        }
    }

    void vendre(){
        int start = 1;
        while (start){
            _merchant.displayPotion();
            std::cout << "Quel potion voulez vous vendre ?" << std::endl;
            std::cout << "1. Poton de soin inferieur : 20 golds" << std::endl;
            std::cout << "2. Potion de force : 40 golds" << std::endl;
            std::cout << "3. Potion de soin superieur : 80 golds" << std::endl;
            std::cout << "4. Retour" << std::endl;
            int choice;
            std::cin >> choice;
            system("clear");
            switch (choice) {
                case 1:
                    if (!_merchant._inventory["Potion de soin inferieur"]){
                        std::cout << "Vous n'avez pas de potion de soin inferieur" << std::endl;
                        break;
                    }
                    _merchant._inventory["Potion de soin inferieur"] -= 1;
                    _merchant._gold += 20;
                    break;
                case 2:
                    if (!_merchant._inventory["Potion de force"]){
                        std::cout << "Vous n'avez pas de potion de force" << std::endl;
                        break;
                    }
                    _merchant._inventory["Potion de force"] -= 1;
                    _merchant._gold += 40;
                case 3:
                    if (!_merchant._inventory["Potion de soin superieur"]){
                        std::cout << "Vous n'avez pas de potion de soin superieur" << std::endl;
                        break;
                    }
                    _merchant._inventory["Potion de soin superieur"] -= 1;
                    _merchant._gold += 80;
                    break;
                case 4:
                    start = 0;
                    break;
            }
            _merchant.displayInventory();
        }
    }

    int loop(){
        _merchant.displayInventory();
        std::cout << "Que voulez vous faire ?" << std::endl;
        std::cout << "1. Poster une quete" << std::endl;
        std::cout << "2. Vendre" << std::endl;
        std::cout << "3. Creer des potions" << std::endl;
        std::cout << "4. Quitter" << std::endl;
        int choice;
        std::cin >> choice;
        system("clear");
        _merchant.displayInventory();
        switch (choice) {
            case 1:
                recruter();
                break;
            case 2:
                vendre();
                break;
            case 3:
                creerPotion();
                break;
            case 4:
                std::cout << "Au revoir" << std::endl;
                return 0;
        }
        return 1;      
    }
};

int main(int ac, char** av) {
    srand(time(NULL));
    int status = 1;
    Game game;
    game.init();
    while(status)
        status = game.loop();
}