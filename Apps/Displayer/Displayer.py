# Copyright 2015 Adafruit Industries.
# Author: Tony DiCola
# License: GNU GPLv2, see LICENSE.txt
import ConfigParser
import importlib
import os
import re
import sys
import signal
import time

import pygame

class Displayer(object):

    def __init__(self):
        self._bgcolor = (0,0,0)
        self._fgcolor = (255,255,255)
        pygame.display.init()
        pygame.font.init()
        pygame.mouse.set_visible(False)
        size = (pygame.display.Info().current_w, pygame.display.Info().current_h)
        self._screen = pygame.display.set_mode(size, pygame.FULLSCREEN)
        self._blank_screen()
        self._small_font = pygame.font.Font(None, 25)
        self._big_font   = pygame.font.Font(None, 250)
        self._running    = True
        self._source = "/var/log/rpi_logger.log"

    def _blank_screen(self):
        """Render a blank screen filled with the background color."""
        self._screen.fill(self._bgcolor)
        pygame.display.update()

    def _render_text(self, message, font=None):
        """Draw the provided message and return as pygame surface of it rendered
        with the configured foreground and background color.
        """
        # Default to small font if not provided.
        if font is None:
            font = self._small_font
        return font.render(message, True, self._fgcolor, self._bgcolor)

    def _render_log(self, lines):
        i=0
        for line in lines:
          self._idle_message(line, i)
          i=i+1
          pygame.display.update()
        
        
    def _idle_message(self, message, line):
        if line==0:
            self._screen.fill(self._bgcolor)
        label = self._render_text(message[:-1])
        lw, lh = label.get_size()
        sw, sh = self._screen.get_size()
        self._screen.blit(label, (10, (lh+5)*line))
        pygame.display.update()

  
    def _tail(self, f, n):
        stdin,stdout = os.popen2("tail -n" + n + " " + f + " | tac")
        stdin.close()
        lines = stdout.readlines(); stdout.close()
        return lines

    def run(self):
        prev = ''
        while True:
            next = ''.join(self._tail(self._source, "50"))
            if not prev == next:
                prev = next
                print('display!')
                self._render_log(self._tail(self._source, "50"))
            time.sleep(15)
            break
    

    def quit(self):
        pygame.quit()


# Main entry point.
if __name__ == '__main__':
    print('Starting daemon.')
    d = Displayer()
    d.run()
    d.quit()
