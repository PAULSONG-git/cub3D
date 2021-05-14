#include <stdio.h>
#include <stdlib.h>

#define  MAPX   11
#define  MAPY   15

int resc(int **tmp, int *flag, int x, int y)
{
	if (tmp[x][y] == 1 && x != 0 && y != 0)
		tmp[x][y] = 5;

	if (tmp[x][y+1] == 1)
		resc(tmp, flag, x, y + 1);
	if (y > 0)
		if (tmp[x][y-1] == 1)
			resc(tmp, flag, x, y - 1);
	if (x < MAPX-1)
		if (tmp[x+1][y] == 1)
			resc(tmp, flag, x+1, y);	
	if (x > 0)
		if (tmp[x-1][y] == 1)
			resc(tmp, flag, x-1, y);
	
	if (x == 0 && y == 0 && *flag)
		printf("invaid");
	*flag = 1;
	return (0);
	
}

int	main(void)
{
	static int map[MAPX][MAPY] = {  /* warning: index order is [x][y] */
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
	{1, 1, 0, 1, 0, 0, 0, 1, 0, 2, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 2, 0, 1, 0, 0},
	{1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
	{1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	int **tmp;
	int flag = 0;

	if (!(tmp = (int **)malloc(sizeof(int *) * MAPX)))
		return (-1);
	for (int i = 0; i < MAPX; i++)
	{
		if (!(tmp[i] = (int *)malloc(sizeof(int) * (MAPY))))
			return (-1);
	}
	for (int i = 0; i < MAPX; i++)
	{
		for (int j = 0; j < MAPY; j++)
		{
			tmp[i][j] = map[i][j];
		}
	}
	
	resc(tmp, &flag, 0, 0);

	for( int y=MAPY-1; y>=0; y-- ) {
        	for( int x=0; x<MAPX; x++ ) {
            printf("%d ", tmp[x][y]);
        }
        putchar('\n');
    }
	free(tmp);
	return (0);
}
