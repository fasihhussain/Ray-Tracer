#include "ViewPlane.hpp"


int ViewPlane::get_hres() const {
    return hres;
}

int ViewPlane::get_vres() const {
    return vres;
}

void ViewPlane::set_hres(int hres) {
    this->hres = hres;
}

void ViewPlane::set_vres(int vres) {
    this->vres = vres;
}