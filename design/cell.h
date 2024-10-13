#pragma once

#include "common.h"
#include "formula.h"
#include <memory>
#include <string>
#include <string_view>
#include <variant>
#include <optional>
#include <unordered_set>

class Cell : public CellInterface 
{
    public:

        Cell();
        ~Cell();

        void Set(std::string text) override;
        void Clear();

        Value GetValue() const override;
        std::string GetText() const override;
        std::vector<Position> GetReferencedCells() const override;

    private:

        class Impl;
        class EmptyImpl;
        class TextImpl;
        class FormulaImpl;

        bool IsCircularDependency(const Impl& impl) const;
        void InvalidateCache();

        std::unique_ptr<Impl> impl_;
        SheetInterface& sheet_;
        
        struct CellHasher
        {
            size_t operator()(const Cell* cell) const 
            {
                return cell_hasher(std::get<double>(cell->GetValue()));
            }

            private:

            std::hash<double> cell_hasher;
        };

        // Контейнер указателей ячеек, на которые ссылается данная ячейка (поиск циклических зависимостей)
        std::unordered_set<Cell*, CellHasher> referenced_to_;
        // Контейнер указателей ячеек, которые ссылается на данную ячейку (инвалидация кеша)
        std::unordered_set<Cell*, CellHasher> referenced_by_;
        // Если кэш валидный, optional хранит Value
        mutable std::optional<FormulaInterface::Value> cache_;
};