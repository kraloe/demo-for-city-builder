#include "CustomCell.h"
#include <stdexcept>

std::vector<CustomCell::CustomCell_Infra_Data> CustomCell::CustomCell_Infra_Datalist;

CustomCell::CustomCell(const Image& import_image){
    Import_Image_To_CustomCell_Infra_DataList(import_image);
}
CustomCell::~CustomCell() {}

void CustomCell::Import_Image_To_CustomCell_Infra_DataList(const Image& import_image){
    unsigned w=import_image.width, h=import_image.height;
    CustomCell_Infra_Data infra{w,h};
    infra.pixels.resize((size_t)w*h);
    for(unsigned y=0;y<h;++y){
        for(unsigned x=0;x<w;++x){
            infra.pixels[(size_t)y*w+x] = image_get_pixel(import_image,(int)x,(int)y);
        }
    }
    CustomCell_Infra_Datalist.push_back(std::move(infra));
}

const CustomCell::CustomCell_Infra_Data& CustomCell::Get_CustomCell_Infra_Data(int i) const{
    if(i<0 || i>=(int)CustomCell_Infra_Datalist.size()) throw std::out_of_range("CustomCell index");
    return CustomCell_Infra_Datalist[(size_t)i];
}
