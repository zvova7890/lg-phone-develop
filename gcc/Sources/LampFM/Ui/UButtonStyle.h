#ifndef UBUTTONSTYLE_H
#define UBUTTONSTYLE_H


#include <gl.h>
#include <Graph/Brush.h>



class UButtonStyle
{
public:
    UButtonStyle();



private:

    GLColor m_textColor;
    Brush m_background, m_border;
};

#endif // UBUTTONSTYLE_H
