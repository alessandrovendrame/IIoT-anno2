from sys import stdout
import pygame
from pygame.locals import*
import numpy as np

combinazioni=0
already_drawn = set()
coords = []
img = pygame.image.load('./img/quad.png')
black = (0, 0, 0)
w = 1200
h = 920
scroll_y = 0
scroll_x = 0
running = True
partY = 0
partX = 0
aux=[]

def polyminoes(n, points):
    if n == 0:
        poly_id = polymino_id(points)
        if checked(poly_id,already_drawn):
            print_polymino(points)
            already_drawn.add(poly_id)
    else:
        available = set()
        for (x, y) in points:
            if x > 0:
                available.add((x - 1, y))
            if y > 0:
                available.add((x, y - 1))
            available.add((x + 1, y))
            available.add((x, y + 1))
        for p in points:
            available.discard(p)
        for p in available:
            polyminoes(n - 1, points + [p])

def polymino_id(points):
    poly_id = []
    ausilio = []
    for p in points:
        ausilio.append(p)
    poly_id.append(ausilio)
    print(poly_id)
    return poly_id

def checked(poly_id,already_drawn):
    for p in poly_id:
        if ((p not in already_drawn) and (np.rot90(p) not in already_drawn) and (np.rot90(p,2) not in already_drawn) and (np.rot90(p,3) not in already_drawn)):
                return True
def print_polymino(points):
    X, Y = max(p[0] for p in points), max(p[1] for p in points)
    for y in range(Y + 1):
        for x in range(X + 1):
            stdout.write('#' if (x, y) in points else ' ')
        stdout.write('\n')
    stdout.write('\n')
    for p in points:
        coords.append([p,False])
    #print(coords)

n = int(input("Inserisci numero di quadratini: "))
polyminoes(n-1, [(0, 0)])

screen = pygame.display.set_mode((w, h))
intermediate = pygame.surface.Surface((5000, 65000))
screen.fill((black))

for p in already_drawn:
    combinazioni+=1

print("Le combinazioni con ",n," quadratini sono: ", combinazioni )

for p in coords:
    aux.append(p[0][0])
    x = partX + p[0][0]*10
    y = partY + p[0][1]*10
    intermediate.blit(img, (x, y))
    if (coords.index(p) + 1) % n == 0:
        partX+=20
        partX += max(aux)*10
        #print("aux: " , aux)
        aux=[]
    if (coords.index(p) + 1) % (n*27) == 0:
        partY += n*10
        partX = 0
    p[1]=True

while running:
    for event in pygame.event.get():
        key=pygame.key.get_pressed()
        if event.type == pygame.KEYDOWN:
            if key[pygame.K_LEFT] : scroll_x = min(scroll_x+30, 0)
            if key[pygame.K_RIGHT]: scroll_x = max(scroll_x-30,-1920)
            if key[pygame.K_UP]: scroll_y = min(scroll_y + 30, 0)
            if key[pygame.K_DOWN]: scroll_y = max(scroll_y - 30, -1080)
        if event.type == pygame.QUIT:
            running = False
    screen.blit(intermediate, (scroll_x, scroll_y))
    pygame.display.flip()
pygame.quit()
