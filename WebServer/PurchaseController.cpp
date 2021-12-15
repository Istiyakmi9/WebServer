#include "PurchaseController.h"
#include"JsonManager.h"

std::string PurchasedController::addPurchedItems(std::string param) {
	auto paramterMap = JsonManager::toRequestMap(param);

	delete paramterMap;
	return "";
}
