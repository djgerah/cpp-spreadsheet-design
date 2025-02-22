#pragma once

#include "common.h"
#include "formula.h"

#include <functional>
#include <optional>
#include <unordered_set>

class Cell : public CellInterface 
{
    public:

        Cell(Sheet& sheet);
        ~Cell();

        void Set(std::string text);
        void Clear();
        Value GetValue() const override;
        std::string GetText() const override;
        bool IsReferenced() const;
        std::vector<Position> GetReferencedCells() const override;

    private:

        class Impl;
        class EmptyImpl;
        class TextImpl;
        class FormulaImpl;

        // Добавьте поля и методы для связи с таблицей, проверки циклических 
        // зависимостей, графа зависимостей и т. д.
        bool IsCircularDependency(const Impl& impl) const;
        void UpdateDependence();
        void InvalidateCache();
    
        std::unique_ptr<Impl> impl_;
        Sheet& sheet_;

        // Контейнер указателей ячеек, на которые ссылается данная ячейка l_nodes (поиск циклических зависимостей)
        std::unordered_set<Cell*> referenced_to_;
        // Контейнер указателей ячеек, которые ссылается на данную ячейку r_nodes (инвалидация кеша)
        std::unordered_set<Cell*> referenced_by_;
};
