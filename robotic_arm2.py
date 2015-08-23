import pygtk
pygtk.require('2.0')
import gtk
import serial

s=serial.Serial(0,2400)
class ButtonBoxExample:
    
    def callback_move_left(self, widget, data=None):
        s.write('a')
        
    def callback_move_right(self, widget, data=None):
        s.write('d')
    
    def callback_move_up(self, widget, data=None):
        s.write('w')
        
    def callback_move_down(self, widget, data=None):
        s.write('s')
        
    def callback_pick(self, widget, data=None):
        s.write('p')
        
    def callback_drop(self, widget, data=None):
        s.write('o')
        
    def callback_stop(self, widget, data=None):
        s.write('x')
        
    # Create a Button Box with the specified parameters
    def create_lr_box(self, horizontal, title, spacing, layout):
        frame = gtk.Frame(title)

        if horizontal:
            bbox = gtk.HButtonBox()
        else:
            bbox = gtk.VButtonBox()

        bbox.set_border_width(5)
        frame.add(bbox)

        # Set the appearance of the Button Box
        bbox.set_layout(layout)
        bbox.set_spacing(spacing)

        button_left = gtk.Button("Move Left")
        button_left.connect("clicked", self.callback_move_left, "Move Left")
        bbox.add(button_left)
        
        button_right = gtk.Button("Move Right")
        button_right.connect("clicked", self.callback_move_right, "Move Right")
        bbox.add(button_right)       
        
      
        return frame

    # Create a Button Box with the specified parameters
    def create_ud_box(self, horizontal, title, spacing, layout):
        frame = gtk.Frame(title)

        if horizontal:
            bbox = gtk.HButtonBox()
        else:
            bbox = gtk.VButtonBox()

        bbox.set_border_width(5)
        frame.add(bbox)

        # Set the appearance of the Button Box
        bbox.set_layout(layout)
        bbox.set_spacing(spacing)

        button_up = gtk.Button("Move Up")
        button_up.connect("clicked", self.callback_move_up, "Move Up")
        bbox.add(button_up)
        
        button_down = gtk.Button("Move Down")
        button_down.connect("clicked", self.callback_move_down, "Move Down")
        bbox.add(button_down)    

        return frame

    # Create a Button Box with the specified parameters
    def create_pd_box(self, horizontal, title, spacing, layout):
        frame = gtk.Frame(title)

        if horizontal:
            bbox = gtk.HButtonBox()
        else:
            bbox = gtk.VButtonBox()

        bbox.set_border_width(5)
        frame.add(bbox)

        # Set the appearance of the Button Box
        bbox.set_layout(layout)
        bbox.set_spacing(spacing)

        button_pick = gtk.Button("Pick")
        button_pick.connect("clicked", self.callback_pick, "Pick")
        bbox.add(button_pick)
        
        button_drop = gtk.Button("Drop")
        button_drop.connect("clicked", self.callback_drop, "Drop")
        bbox.add(button_drop)    

        return frame

    # Create a Button Box with the specified parameters
    def create_stop_box(self, horizontal, title, spacing, layout):
        frame = gtk.Frame(title)

        if horizontal:
            bbox = gtk.HButtonBox()
        else:
            bbox = gtk.VButtonBox()

        bbox.set_border_width(5)
        frame.add(bbox)

        # Set the appearance of the Button Box
        bbox.set_layout(layout)
        bbox.set_spacing(spacing)

        button_stop = gtk.Button("STOP")
        button_stop.connect("clicked", self.callback_stop, "STOP")
        bbox.add(button_stop)           

        return frame

    # Create a Button Box with the specified parameters
    def __init__(self):
        window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        window.set_title("Button Boxes")

        window.connect("destroy", lambda x: gtk.main_quit())

        window.set_border_width(10)

        main_vbox = gtk.VBox(False, 0)
        window.add(main_vbox)

        frame_vert = gtk.Frame("ROBOTIC ARM CONTROL")
        main_vbox.pack_start(frame_vert, True, True, 10)

        hbox = gtk.HBox(False, 0)
        hbox.set_border_width(10)
        frame_vert.add(hbox)

        hbox.pack_start(self.create_lr_box(False, "Left/Right Control",
                                         5, gtk.BUTTONBOX_SPREAD),
                        True, True, 0)

        hbox.pack_start(self.create_ud_box(False, "Up/Down Control",
                                         30, gtk.BUTTONBOX_SPREAD),
                        True, True, 5)
                        
        hbox.pack_start(self.create_pd_box(False, "Pick/Drop Control",
                                         30, gtk.BUTTONBOX_SPREAD),
                        True, True, 5)

        hbox.pack_start(self.create_stop_box(False, "STOP Control",
                                         20, gtk.BUTTONBOX_SPREAD),
                        True, True, 5)

        """hbox.pack_start(self.create_bbox(False, "STOP",
                                         20, gtk.BUTTONBOX_END),
                        True, True, 5)"""

        window.show_all()

def main():
    # Enter the event loop
    gtk.main()
    s.write('x')
    s.close();
    return 0

if __name__ == "__main__":
    ButtonBoxExample()
    main()