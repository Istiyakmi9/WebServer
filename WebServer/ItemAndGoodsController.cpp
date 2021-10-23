#include"ItemAndGoodsController.h"
#include"ProductModal.h"

std::string ItemAndGoodsController::AddEditStockItem(std::string args) {
	std::unique_ptr<ProductModal> productModal(new ProductModal());
	productModal->setPrivateFieldsValue(args);
	return "";
}