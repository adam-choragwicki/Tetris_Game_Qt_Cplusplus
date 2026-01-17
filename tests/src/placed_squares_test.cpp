#include "common_test_fixture.h"
#include "placed_squares.h"

class PlacedSquaresTest : public CommonTestFixture
{
protected:
    PlacedSquaresTest()
    {}

    void fillRow(const int row)
    {
        for (int i = 1; i <= 10; ++i)
        {
            placedSquares_.addSquare(Coordinates{i, row}, DEFAULT_SQUARE_COLOR);
        }
    }

    bool isRowEmpty(const int row) const
    {
        for (int i = 1; i <= 10; i++)
        {
            if (placedSquares_.isTileAtCoordinatesOccupied(Coordinates{i, row}))
            {
                return false;
            }
        }

        return true;
    }

    bool isRowFull(const int row) const
    {
        for (int i = 1; i <= 10; i++)
        {
            if (!placedSquares_.isTileAtCoordinatesOccupied(Coordinates{i, row}))
            {
                return false;
            }
        }

        return true;
    }

    PlacedSquares placedSquares_;

private:
    void SetUp() override
    {}

    void TearDown() override
    {}
};

TEST_F(PlacedSquaresTest, CreatePlacedSquares)
{
    EXPECT_EQ(placedSquares_.size(), 0);
}

TEST_F(PlacedSquaresTest, AddSquare)
{
    EXPECT_FALSE(placedSquares_.isTileAtCoordinatesOccupied(Coordinates{5, 5}));

    placedSquares_.addSquare(Coordinates{5, 5}, DEFAULT_SQUARE_COLOR);

    EXPECT_TRUE(placedSquares_.isTileAtCoordinatesOccupied(Coordinates{5, 5}));
}

TEST_F(PlacedSquaresTest, FindFullRows)
{
    fillRow(5);
    fillRow(7);

    const auto fullRows = placedSquares_.findFullRowsNumbers();

    EXPECT_EQ(fullRows.size(), 2);
    EXPECT_EQ(fullRows.at(0), 5);
    EXPECT_EQ(fullRows.at(1), 7);
}

TEST_F(PlacedSquaresTest, DropRowsAbove)
{
    constexpr int fullRow = 5;

    fillRow(fullRow);

    constexpr int rowBelow = 6;

    EXPECT_TRUE(isRowFull(fullRow));
    EXPECT_TRUE(isRowEmpty(rowBelow));

    placedSquares_.dropRowsAboveGivenRow(6);

    EXPECT_TRUE(isRowEmpty(fullRow));
    EXPECT_TRUE(isRowFull(rowBelow));
}

TEST_F(PlacedSquaresTest, RemoveFullRow)
{
    constexpr int fullRow = 5;

    fillRow(fullRow);

    EXPECT_TRUE(isRowFull(fullRow));

    placedSquares_.removeRow(fullRow);

    EXPECT_TRUE(isRowEmpty(fullRow));
}
