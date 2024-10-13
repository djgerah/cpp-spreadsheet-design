#pragma once

#include "cell.h"
#include "common.h"
 
#include <functional>
 
class Sheet : public SheetInterface 
{
    public:

        ~Sheet();
    
        void SetCell(Position pos, std::string text) override;
        const CellInterface* GetCell(Position pos) const override;
        CellInterface* GetCell(Position pos) override;
        void ClearCell(Position pos) override;
        bool IsCellValid(int row, int col) const;
        Size GetPrintableSize() const override;
    
        void PrintValues(std::ostream& output) const override;
        void PrintTexts(std::ostream& output) const override;
    
    private:
        // Можете дополнить ваш класс нужными полями и методами
        const CellInterface* CellGetter(Position pos) const;

        std::vector<std::vector<std::unique_ptr<Cell>>> cells_;
};