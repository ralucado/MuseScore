/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "lasso.h"

#include "score.h"

using namespace mu;
using namespace mu::engraving;

namespace mu::engraving {
//---------------------------------------------------------
//   Lasso
//---------------------------------------------------------

Lasso::Lasso(Score* s)
    : EngravingItem(ElementType::LASSO, s)
{
    setVisible(false);
}

//---------------------------------------------------------
//   editDrag
//---------------------------------------------------------

void Lasso::editDrag(EditData& ed)
{
    //Qt::CursorShape cursorShape = Qt::ArrowCursor;
    Lasso::LayoutData* ldata = mutLayoutData();
    switch (int(ed.curGrip)) {
    case 0:
        //cursorShape = Qt::SizeFDiagCursor;
        ldata->bbox.setTopLeft(ldata->bbox.topLeft() + ed.delta);
        break;
    case 1:
        //cursorShape = Qt::SizeBDiagCursor;
        ldata->bbox.setTopRight(ldata->bbox.topRight() + ed.delta);
        break;
    case 2:
        //cursorShape = Qt::SizeFDiagCursor;
        ldata->bbox.setBottomRight(ldata->bbox.bottomRight() + ed.delta);
        break;
    case 3:
        //cursorShape = Qt::SizeBDiagCursor;
        ldata->bbox.setBottomLeft(ldata->bbox.bottomLeft() + ed.delta);
        break;
    case 4:
        //cursorShape = Qt::SizeVerCursor;
        ldata->bbox.setTop(ldata->bbox.top() + ed.delta.y());
        break;
    case 5:
        //cursorShape = Qt::SizeHorCursor;
        ldata->bbox.setRight(ldata->bbox.right() + ed.delta.x());
        break;
    case 6:
        //cursorShape = Qt::SizeVerCursor;
        ldata->bbox.setBottom(ldata->bbox.bottom() + ed.delta.y());
        break;
    case 7:
        //cursorShape = Qt::SizeHorCursor;
        ldata->bbox.setLeft(ldata->bbox.left() + ed.delta.x());
        break;
    }

    // ed.view()->setCursor(QCursor(cursorShape));
}

//---------------------------------------------------------
//   gripsPositions
//---------------------------------------------------------

std::vector<mu::PointF> Lasso::gripsPositions(const EditData&) const
{
    const auto box(layoutData()->bbox);
    return {
        box.topLeft(),
        box.topRight(),
        box.bottomRight(),
        box.bottomLeft(),
        PointF(box.x() + box.width() * .5, box.top()),
        PointF(box.right(), box.y() + box.height() * .5),
        PointF(box.x() + box.width() * .5, box.bottom()),
        PointF(box.left(), box.y() + box.height() * .5)
    };
}
}
