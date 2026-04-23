#include <iostream>
#include <vector>
#include <utility>

typedef std::vector<std::vector<char>> grid_t;


void delete_column(grid_t &grid, int column_to_delete); //Forward declarations
void delete_row(grid_t &grid, int row_to_delete);


char int_to_char_converter(int int_value) //Converts int values to char values
{
    char char_value {};
    
    switch (int_value)
    {
        case 0:
            char_value = '0';
            break;
        case 1:
            char_value = '1';
            break;
        case 2:
            char_value = '2';
            break;
        case 3:
            char_value = '3';
            break;
        case 4:
            char_value = '4';
            break;
        case 5:
            char_value = '5';
            break;
        case 6:
            char_value = '6';
            break;
        case 7:
            char_value = '7';
            break;
        case 8:
            char_value = '8';
            break;
        default:
            char_value = '?';
            break;
    }
    
    return char_value;
}


int get_grid_size()
{
    int grid_size {};
    std::cout<<"What is the grid size? (Will be square, so only input one value)\n";
    std::cin>>grid_size;
    
    grid_size = grid_size + 2;
    
    return grid_size;
}

std::pair<int, int> get_starting_points()
{
    std::cout<<"\nPlease input your starting x point\n";
    int x {};
    std::cin>>x;
    std::cout<<"\nPlease input your starting y point\n";
    int y {};
    std::cin>>y;
    
    return {x, y};
}

void print_grid(grid_t grid, int grid_size)
{
    std::cout<<"\n";
    
    for (int i = 0; i < grid_size; ++i)
    {
        for (int j = 0; j < grid_size; ++j)
        {
            std::cout<<grid[i][j]<<" ";
        }
        std::cout<<"\n";
    }
}

//Places the mines
void place_mines(grid_t &grid, int grid_size)
{
    auto [starting_x, starting_y] = get_starting_points();
    
    int mine_amount = (grid_size * grid_size) / 6;
    
    for (int i = 0; i < mine_amount; ++i)
    {
        int x {};
        int y {};
        
        do 
        {
            x = rand() % grid_size;
            y = rand() % grid_size;
        } while (grid[x][y] == 'x' || (x == starting_x && y == starting_y) || x == (grid_size - 1) || y == (grid_size - 1) || x == 0 || y == 0);
        
        grid[x][y] = 'x';
    }
}

//Finds all mines adjacent and diagonal to selected tile and returns the number
char mines_in_proximity_finder(grid_t grid, int i, int j)
{
    int mines_in_proximity = {0};
    
    for (int k = -1; k < 2; ++k)
    {
        for (int l = -1; l < 2; ++l)
        {
            if (grid[i + k][j + l] == 'x')
            {
                mines_in_proximity++;
            }
        }
    }
    
    char mines_in_proximity_char = int_to_char_converter(mines_in_proximity);
    
    return mines_in_proximity_char;
}

//Tests every tile (except for edges) for mines and assigns the number of mines around the selected tile 
//to the selected tile
void find_mines(grid_t &grid, int grid_size)
{
    int mines_in_proximity {};
    
    for (int i = 0; i < grid_size; ++i)
    {
        for (int j = 0; j < grid_size; ++j)
        {
            if (grid[i][j] != 'x' && (i != 0 && j != 0 && i != (grid_size - 1) && j != (grid_size - 1)))
            {
                grid[i][j] = mines_in_proximity_finder(grid, i, j);
            }
        }
    }
}

void trim_grid(grid_t &grid, int grid_size)
{
    int column_to_delete = grid_size - 1;
    delete_column(grid, column_to_delete);
    
    column_to_delete = 0;
    delete_column(grid, column_to_delete);
    
    int row_to_delete = grid_size - 1;
    delete_row(grid, row_to_delete);
    
    row_to_delete = 0;
    delete_row(grid, row_to_delete);
}

void delete_column(grid_t &grid, int column_to_delete)
{
    for (unsigned i = 0; i < grid.size(); ++i)
    {
        if (grid[i].size() > column_to_delete)
        {
            grid[i].erase(grid[i].begin() + column_to_delete);
        }
    }
}

void delete_row(grid_t &grid, int row_to_delete)
{
    if (grid.size() > row_to_delete)
    {
        grid.erase(grid.begin() + row_to_delete);
    }
}

int main()
{
    srand((unsigned) time(NULL));
    
    int grid_size = get_grid_size();
    
    grid_t grid(grid_size, std::vector<char>(grid_size, '0')); //Initializes the grid
    
    place_mines(grid, grid_size);
    
//print_grid(grid, grid_size);
    
    find_mines(grid, grid_size); //Assigns number of adjacent mines to non-mine tiles

    trim_grid(grid, grid_size);
    
    print_grid(grid, grid_size - 2);

    return 0;
}

