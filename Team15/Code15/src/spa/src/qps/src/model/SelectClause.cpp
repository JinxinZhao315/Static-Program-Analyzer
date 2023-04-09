#include "qps/include/model/SelectClause.h"

SelectClause::SelectClause() : Clause(SELECT) {}

SelectClause::~SelectClause() {}

SelectClause::SelectClause(std::vector<Elem*>& selectedElements) : Clause(SELECT) {
    this->selectedElements = selectedElements;
    for (Elem* e : selectedElements) {
        addSyn(e->getSynName());
    }
}

std::vector<Elem*> SelectClause::getSelectedElements() {
    return this->selectedElements;
}
