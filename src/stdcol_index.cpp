#include <stdcol_index.h>

using namespace stdcol;

constexpr const index::int_type findex::not_found;

index::index() : value(0) {}

index::index(const int_type& value) : value(value) {}

index::int_type& index::operator=(const int_type& value) {
    this->value = value;
    return this->value;
}

index::operator stdcol::index::int_type&() { return value; }

index::operator const stdcol::index::int_type&() const { return value; }

findex::findex() : index(findex::not_found) {}

findex::findex(const int_type& value) : index(value) {}

bool findex::found() const { return value != findex::not_found; }
