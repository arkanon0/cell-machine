#ifndef __gl_h_
#include <GL/glut.h>
#endif
#ifndef _cellTypeEnum
#include "cellType.cc"
#endif
#ifndef _GLIBCXX_TUPLE
#include <tuple>
#endif
#ifndef _directionEnum
#include "direction.cc"
#endif
#ifndef _cellFunctions
#include "cellFunctions.cc"
#endif

typedef bool2 std::tuple<bool, bool>

class Cell {
    public:
        int cellID;
        cellType type;

        virtual void kill(bool forever) {
            cellgrid[this->x][this->y] = NULL;
            if (forever) {delete this};
            else {
                this->x = this->xstart;
                this->y = this->ystart;
            }
        }

        void setposition(int x, int y) {
            this->x = x;
            this->y = y;
        }

        virtual std::tuple<bool, bool> push(direction dir, int bias) {
            int xoff = this->x;
            int yoff = this->y;
            switch (dir) {
                case direction::RIGHT:
                    xoff++;
                    break;
                case direction::DOWN:
                    yoff++;
                    break;
                case direction::LEFT:
                    xoff--;
                    break;
                case direction::UP:
                    yoff--;
                    break;
            }
            if (xoff < 0 || xoff > width || yoff < 0 || yoff > height) {
                return new bool2(false, false);
            }
            if (grid[xoff][yoff] == NULL) {
                this->setposition(xoff, yoff);
                return new bool2(true, false);
            }

            bool2 values = cellgrid[xoff][yoff].push(dir, bias);
            if (values[1]) {
                this->kill(this->generated);
                return new bool2(true, false);
            }
            else if (values[0]) {
                this->setposition(xoff, yoff);
            }
            return new bool2(values[0], false);
        }

    protected:
    private:
        unsigned int xstart;
        unsigned int ystart;
        unsigned int x;
        unsigned int y;
        bool generated = false;
        bool suppress = false;
};

#define _CellClass 1

