#!/usr/bin/env python3

import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = "hide"
import pygame as pg
import json
import sys

SCREEN_SIZE_X   = 1200
SCREEN_SIZE_Y   = 600

BACKGROUD_COLOR = (0, 0, 0)
CELL_COLOR      = (255,0,0)
CELLEDGE_COLOR  = (255,128,60)
PIN_COLOR       = (0,255,0)
WIRE0_COLOR     = (0,0,255)
WIRE1_COLOR     = (0,255,255)
VIA_COLOR       = (255,255,255)
TEXT_COLOR      = (255,255,255)
EDGE_COLOR      = (255,255,66)

PPU             = 40 # pixels per unit
FONT_SIZE       = 20
BORDER_SIZE     = 4

def LoadJson(fname):
    with open(fname) as f:
        return json.load(f)
        
# Draw primitives in unit coordinates with (0,0) at lower left
def DrawRect(base, rect, color, width = 0):
    pg.draw.rect(screen, color, pg.Rect(round(rect[0]*PPU-base[0]), round(SCREEN_SIZE_Y-(rect[1]+rect[3])*PPU+base[1]), round(rect[2]*PPU), round(rect[3]*PPU)), round(width))
def DrawRectXY(base, rect, color):
    DrawRect(base, [rect[0], rect[1], rect[2]-rect[0], rect[3]-rect[1]], color)
def DrawText(base, text, x, y, area):
    text_surface = font.render(text, False, (0, 0, 0))
    screen.blit(text_surface, (x*PPU-base[0], SCREEN_SIZE_Y-y*PPU-FONT_SIZE+base[1]), area = (0, 0, area[0]*PPU, area[1]*PPU))

# Draw cell        
def DrawCell(base, name, cell, cells):
    x = cell[1]
    y = cell[2]
    c = cells[cell[0]]
    wdt = c["width"]
    # draw cell body & frame
    DrawRect(base, [x, y, wdt, 1], CELL_COLOR)
    DrawRect(base, [x, y, wdt, 1], CELLEDGE_COLOR, BORDER_SIZE)
    # draw name
    DrawText(base, name, x, y, (wdt, 1))
    # draw pins
    for pin in c["pins"]:
        p = c["pins"][pin]
        DrawRect(base, [x+p[0], y+p[1], p[2]-p[0], p[3]-p[1]], PIN_COLOR)

# Draw wire
def DrawWire(base, wire, color):
    DrawRectXY(base, wire, color)

# Check command line params
if len(sys.argv) != 3:
    print("Usage:", sys.argv[0], "cells_json output_json")
    sys.exit(1)

# Initializing pygame
pg.init()
font = pg.font.SysFont('Comic Sans MS', FONT_SIZE)
screen = pg.display.set_mode((SCREEN_SIZE_X, SCREEN_SIZE_Y))
pg.display.set_caption('Cells')
clock = pg.time.Clock()
running = True
 
# Load data from JSONs
cells = LoadJson(sys.argv[1])
placed = LoadJson(sys.argv[2])

base = [-BORDER_SIZE, -BORDER_SIZE]

# Main loop
while running:
    clock.tick(100)
    screen.fill(BACKGROUD_COLOR)
    
    # Draw border
    size = placed["size"]
    DrawRect(base, [-(BORDER_SIZE/PPU), -(BORDER_SIZE/PPU), size[0]+2*(BORDER_SIZE/PPU), size[1]+2*(BORDER_SIZE/PPU)], EDGE_COLOR, BORDER_SIZE)
    
    # Draw cells
    for c in placed["cells"]:
        DrawCell(base, c, placed["cells"][c], cells)
    
    # Draw wires & vias
    for w in placed["wires0"]:
        DrawWire(base, w, WIRE0_COLOR)
    for w in placed["wires1"]:
        DrawWire(base, w, WIRE1_COLOR)
    for w in placed["via"]:
        DrawWire(base, w, VIA_COLOR)
    
    # Handle keyboard events
    for e in pg.event.get():
        if e.type == pg.KEYDOWN:
            if e.key == pg.K_LEFT:
                base[0] -= PPU
            elif e.key == pg.K_RIGHT:
                base[0] += PPU
            elif e.key == pg.K_UP:
                base[1] += PPU
            elif e.key == pg.K_DOWN:
                base[1] -= PPU
            elif e.key == pg.K_ESCAPE:
                running = False
        elif e.type == pg.QUIT:
            running = False
    pg.display.flip()
