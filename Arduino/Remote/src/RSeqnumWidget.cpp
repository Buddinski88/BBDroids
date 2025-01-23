#include "RSeqnumWidget.h"

#define NUMROWS 2
#define NUMCOLS 4

RSeqnumWidget::RSeqnumWidget(): RWidget(), c_('?'), nocomm_(true){
    for(int c=0; c<NUMCOLS; c++) for(int r=0; r<NUMROWS; r++) {
        Square s = {true, RDisplay::DARKBLUE};
        squares_.push_back(s);
    }
    needsContentsRedraw_ = true;
    needsFullRedraw_ = true;
}

void RSeqnumWidget::setChar(char c) {
    c_ = c;
    setNeedsFullRedraw(true);
}

Result RSeqnumWidget::draw(ConsoleStream* stream) {
    if(needsFullRedraw_) {
        RDisplay::display.rect(x_, y_, x_+width_, y_+height_, bgCol_, true);
        setNeedsFullRedraw(false);
    }

    if(needsContentsRedraw_) {
        RDisplay::display.text(x_, y_, fgCol_, String(c_));
    }

    if(nocomm_ == true) {
        if(needsContentsRedraw_) {
            RDisplay::display.rect(x_+RDisplay::CHAR_WIDTH+1, y_, x_+width_, y_+height_, frameCol_, false);
            RDisplay::display.line(x_+RDisplay::CHAR_WIDTH+1, y_, x_+width_, y_+height_, frameCol_);
            setNeedsContentsRedraw(false);
        }
        return RES_OK;
    }

    bool dirty = needsContentsRedraw_;
    for(auto& s: squares_) {
        if(s.dirty) {
            dirty = true;
            break;
        }
    }
    if(dirty == false) return RES_OK;
     
    int sqw = (width_-RDisplay::CHAR_WIDTH+1) / NUMCOLS, sqh = height_ / NUMROWS;
    for(int col=0; col<NUMCOLS; col++) {
        for(int row=0; row<NUMROWS; row++) {
            if(squares_[row*NUMCOLS+col].dirty == false && needsContentsRedraw_ == false) continue;
            RDisplay::display.rect(x_+RDisplay::CHAR_WIDTH+1+col*sqw, y_+row*sqh, 
                                   x_+RDisplay::CHAR_WIDTH+1+(col+1)*sqw, y_+(row+1)*sqh, 
                                   squares_[row*NUMCOLS+col].color, true);
        }
    }
    setNeedsContentsRedraw(false);
    setNeedsFullRedraw(false);
    return RES_OK;
}

void RSeqnumWidget::setSquareColor(uint8_t s, uint8_t color) {
    if(s > NUMROWS*NUMCOLS) return;

    setNoComm(false);
    if(squares_[s].color == color) return;
    squares_[s].color = color;
    squares_[s].dirty = true;
}

void RSeqnumWidget::setNoComm(bool yesno) {
    if(yesno == nocomm_) return;
    nocomm_ = yesno;
    setNeedsContentsRedraw();
    setNeedsFullRedraw();
}
