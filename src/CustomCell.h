#pragma once
#include "gl_image.h"
#include "gl_texture.h"
#include <vector>

class CustomCell {
    struct CustomCell_Infra_Data {
        CustomCell_Infra_Data(unsigned int w, unsigned int h) : width(w), height(h) {}
        unsigned int width, height;
        std::vector<Color> pixels;
    };
public:
    CustomCell(const Image& import_image);
    ~CustomCell();
    void Import_Image_To_CustomCell_Infra_DataList(const Image& import_image);
    const CustomCell_Infra_Data& Get_CustomCell_Infra_Data(int index) const;
    int Get_Count_Of_CustomCell_Infra_Datalist() const { return (int)CustomCell_Infra_Datalist.size(); }
private:
    static std::vector<CustomCell_Infra_Data> CustomCell_Infra_Datalist;
};
