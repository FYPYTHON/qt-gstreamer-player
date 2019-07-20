# coding=utf-8

XINI = 30
YINI = 20
XSTEP = 83
YSTEP = 81
XWIDTH = 50
YHEIGHT = 50
WIDTH = 600
HEIGHT = 420


def get_rect(x, y):
    """
    :param x:  第 x 行
    :param y:  第 y 列
    :return:
    y1 : 距离顶部
    width - x2 : 距离右边
    height - y2 : 距离底部
    x1: 距离左边
    """
    x1 = XINI + XSTEP * x
    x2 = x1 + XWIDTH
    y1 = YINI + YSTEP * y
    y2 = y1 + YHEIGHT
    # return x1, y1, y2, x2
    return "%d %d %d %d" % (y1, WIDTH - x2, HEIGHT - y2, x1)


if __name__ == "__main__":
    print(get_rect(5, 1))
    print(get_rect(5, 3))
    print(get_rect(2, 0))