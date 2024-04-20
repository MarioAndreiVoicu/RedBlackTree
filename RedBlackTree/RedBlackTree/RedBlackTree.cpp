#include "RedBlackTree.h"
#include<iostream>

int main()
{
	//std::vector<std::pair<int, std::string>> keyVector = { {10,"Mario"},{7,"test"},{9,"left"},{24,"right"},{25,"a"},{31,"b"},{14,"root"},{44,"c"},{17,"c"},{0,"b"},{8,"e"},{ 12,"a" },{11,"x"} };   //change data type here
	//RBT <int,std::string> RBT(keyVector);  //change data type here

	//either insert elements manually or use the intialization vector above

	RBT<int, std::string> RBT; //change data type here
	int option;
	int key;  //change data type here
	std::string value;//change data type here
	std::cout << "0 for exit\n1 for insert\n2 for deleteKey\n3 for erase\n4 for max\n5 for min\n6 for successor\n7 for predecessor\n8 for find\n9 for display InOrder\n10 for display PreOrder\n11 for display PostOrder\n12 for empty\n13 for clear\n";
	std::cout << "Chose an option: ";
	while (std::cin >> option && option != 0)
	{
		switch (option)
		{
		case 0:
			break;
		case 1:
			std::cout << "What key do you want to insert: ";
			std::cin >> key;
			std::cout << "What value do you want to insert: ";
			std::cin >> value;
			RBT.insert({ key,value });
			break;
		case 2:
			std::cout << "What key do you want to delete: ";
			std::cin >> key;
			RBT.deleteKey(key);
			break;
		case 3:
			std::cout << "What key do you want to delete: ";
			std::cin >> key;
			if (RBT.find(key))
				RBT.erase(RBT.find(key));
			else
				std::cout << "There is no node with the key " << key << " in the RBT\n";
			break;
		case 4:
			std::cout << "Insert the key for the subtree where the search for the max key will be made: ";
			std::cin >> key;
			if (RBT.find(key) != nullptr)
				std::cout << "The max key from the subtree is " << RBT.max(RBT.find(key))->KeyValuePair.first << "\n";
			else
				std::cout << "The key is not in the RBT\n";
			break;
		case 5:
			std::cout << "Insert the key for the subtree where the search for the min key will be made: ";
			std::cin >> key;
			if (RBT.find(key) != nullptr)
				std::cout << "The min key from the subtree is " << RBT.min(RBT.find(key))->KeyValuePair.first << "\n";
			else
				std::cout << "The key is not in the RBT\n";
			break;
		case 6:
			std::cout << "Insert the key for which you want to find the successor: ";
			std::cin >> key;
			if (RBT.find(key))
			{
				if (RBT.successor(RBT.find(key)) != nullptr)
					std::cout << "The successor of " << key << " is " << RBT.successor(RBT.find(key))->KeyValuePair.first << "\n";
				else
					std::cout << "The node with the key " << key << " does not have a successor\n";
			}
			else
				std::cout << "The key is not in the RBT\n";
			break;
		case 7:
			std::cout << "Insert the key for which you want to find the predecessor: ";
			std::cin >> key;
			if (RBT.find(key))
			{
				if (RBT.predecessor(RBT.find(key)) != nullptr)
					std::cout << "The predecessor of " << key << " is " << RBT.predecessor(RBT.find(key))->KeyValuePair.first << "\n";
				else
					std::cout << "The node with the key " << key << " does not have a predecessor\n";
			}
			else
				std::cout << "The key is not in the RBT\n";
			break;
		case 8:
			std::cout << "What key do you want to find: ";
			std::cin >> key;
			if (RBT.find(key))
				std::cout << "The key is in the RBT\n";
			else
				std::cout << "The key is not in the RBT\n";
			break;
		case 9:
			std::cout << "InOrder display: ";
			RBT.displayInOrder();
			std::cout << "\n";
			break;
		case 10:
			std::cout << "PreOrder display: ";
			RBT.displayPreOrder();
			std::cout << "\n";
			break;
		case 11:
			std::cout << "PostOrder display: ";
			RBT.displayPostOrder();
			std::cout << "\n";
			break;
		case 12:
			if (RBT.empty())
				std::cout << "The RBT is empty\n";
			else
				std::cout << "The RBT is not empty\n";
			break;
		case 13:
			RBT.clear();
			break;
		default:
			std::cout << "Invalid option\n";
		}
		std::cout << "Insert an option: ";
	}

	RBT.clear();
	return 0;
}