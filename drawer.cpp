#include "drawer.h"
#include "utilities.h"
#include "coordinates.h"

QGraphicsScene* Drawer::m_pScene = nullptr;

void Drawer::DrawGameArena()
{
    QBrush whiteBrush(GameArenaParameters::WALL_COLOR);
    QPen wallPen(whiteBrush, GameArenaParameters::WALL_THICKNESS);

    /*Left wall*/
    m_pScene->addLine(GameArenaParameters::LEFT_BORDER_X + GameArenaParameters::LEFT_BORDER_X_OFFSET,
                      GameArenaParameters::BOTTOM_Y,
                      GameArenaParameters::LEFT_BORDER_X + GameArenaParameters::LEFT_BORDER_X_OFFSET,
                      GameArenaParameters::TOP_Y,
                      wallPen);

    /*Right wall*/
    m_pScene->addLine(GameArenaParameters::RIGHT_BORDER_X + GameArenaParameters::RIGHT_BORDER_X_OFFSET,
                      GameArenaParameters::BOTTOM_Y,
                      GameArenaParameters::RIGHT_BORDER_X + GameArenaParameters::RIGHT_BORDER_X_OFFSET,
                      GameArenaParameters::TOP_Y,
                      wallPen);

    /*Bottom wall*/
    m_pScene->addLine(GameArenaParameters::LEFT_BORDER_X,
                      GameArenaParameters::BOTTOM_Y + GameArenaParameters::BOTTOM_Y_OFFSET,
                      GameArenaParameters::RIGHT_BORDER_X,
                      GameArenaParameters::BOTTOM_Y + GameArenaParameters::BOTTOM_Y_OFFSET,
                      wallPen);

    /*Top wall*/
    m_pScene->addLine(GameArenaParameters::LEFT_BORDER_X,
                      GameArenaParameters::TOP_Y + GameArenaParameters::TOP_Y_OFFSET,
                      GameArenaParameters::RIGHT_BORDER_X,
                      GameArenaParameters::TOP_Y + GameArenaParameters::TOP_Y_OFFSET,
                      wallPen);
}

void Drawer::DrawSquare(const Coordinates& coordinates, QBrush brush)
{
    m_pScene->addRect((coordinates.GetX() - 1) * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                      (coordinates.GetY() - 1) * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                      GameArenaParameters::BLOCK_SQUARE_SIZE,
                      GameArenaParameters::BLOCK_SQUARE_SIZE,
                      Qt::NoPen,
                      brush);
}

QVector<QGraphicsRectItem*> Drawer::DrawBlock(const QVector<Coordinates>& blockCoordinates, QColor randomColor)
{
    QVector<QGraphicsRectItem*> squaresGraphicsRectPointers;

    QPen randomColorPen(randomColor);
    QBrush randomColorBrush(randomColor);

    for(int i = 0 ; i < blockCoordinates.size(); i++)
    {
        auto squareGraphicsRectItem = m_pScene->addRect((blockCoordinates.at(i).GetX() - 1) * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                                        (blockCoordinates.at(i).GetY() - 1) * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                                        GameArenaParameters::BLOCK_SQUARE_SIZE,
                                                        GameArenaParameters::BLOCK_SQUARE_SIZE,
                                                        randomColorPen,
                                                        randomColorBrush);

        squaresGraphicsRectPointers.append(squareGraphicsRectItem);
    }

    return squaresGraphicsRectPointers;
}

void Drawer::DrawAllPlacedBlocks(const PlacedSquares& placedBlocks)
{
    /*Placed blocks are first removed from scene and then placed again*/
    RemoveAllPlacedBlocks();

    for(auto& coordinates : placedBlocks.GetPlacedBlocksMap().keys())
    {
        if(placedBlocks.GetPlacedBlocksMap().value(coordinates) == PlacedSquares::SquarePresence::SQUARE_PRESENT)
        {
            DrawSquare(coordinates, PlacedSquares::PLACED_SQUARES_COLOR);
        }
    }
}

void Drawer::RemoveAllPlacedBlocks()
{
    for(auto& graphicItem : m_pScene->items())
    {
        /*Remove all squares from scene*/
        if(dynamic_cast<QGraphicsRectItem*>(graphicItem))
        {
            m_pScene->removeItem(graphicItem);
        }
    }
}

void Drawer::Debug_PrintItemsCurrentlyOnScene()
{
    qDebug() << "GRAPHICAL ITEMS CURRENTLY ON SCENE (" << m_pScene << ")";

    int index = 1;

    for(auto* item : m_pScene->items())
    {
        qDebug() << index << ". " << item;
        index++;
    }
}

void Drawer::Debug_DrawAllPossibleSquares()
{
    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);

    for(int column = 0; column < GameArenaParameters::MAX_BLOCK_COLUMNS; ++column)
    {
        for(int row = 0; row < GameArenaParameters::MAX_BLOCK_ROWS; ++row)
        {
            /*Different block color every second column*/
            if(column % 2 == 0)
            {
                if(row % 2 == 0) /*Different block color every second row*/
                {
                    m_pScene->addRect(column * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                      row * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                      GameArenaParameters::BLOCK_SQUARE_SIZE,
                                      GameArenaParameters::BLOCK_SQUARE_SIZE,
                                      Qt::NoPen,
                                      blueBrush);
                }
                else
                {
                    m_pScene->addRect(column * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                      row * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                      GameArenaParameters::BLOCK_SQUARE_SIZE,
                                      GameArenaParameters::BLOCK_SQUARE_SIZE,
                                      Qt::NoPen,
                                      redBrush);
                }
            }
            else
            {
                if(row % 2 != 0)
                {
                    m_pScene->addRect(column * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                      row * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                      GameArenaParameters::BLOCK_SQUARE_SIZE,
                                      GameArenaParameters::BLOCK_SQUARE_SIZE,
                                      Qt::NoPen,
                                      blueBrush);
                }
                else
                {
                    m_pScene->addRect(column * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                      row * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                      GameArenaParameters::BLOCK_SQUARE_SIZE,
                                      GameArenaParameters::BLOCK_SQUARE_SIZE,
                                      Qt::NoPen,
                                      redBrush);
                }
            }
        }
    }
}
