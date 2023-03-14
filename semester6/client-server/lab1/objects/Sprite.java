package objects;

import java.awt.Color;
import java.awt.Graphics;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import util.Vector2i;

public abstract class Sprite
{
    public enum State
    { ALIVE, FREEZED }

    protected int x_, y_, w_, h_, speed_;
    protected Color color_;

    private State state_;
    private boolean border_showing_;

    public
    Sprite(int x, int y, int w, int h, Color color)
    {
        x_     = x;
        y_     = y;
        w_     = w;
        h_     = h;
        color_ = color;
        speed_ = 0;

        state_ = State.FREEZED;
    }

    public abstract Sprite
    move(Vector2i direction);

    public Sprite
    set_speed(int speed)
    { speed_ = speed; return this; }

    public Sprite
    freeze()
    { state_ = State.FREEZED; return this; }

    public Sprite
    liveup()
    { state_ = State.ALIVE; return this; }

    public boolean
    alive()
    { return state_ == State.ALIVE; }

    public boolean
    freezed()
    { return state_ == State.FREEZED; }

    public Sprite
    set_border_showing(boolean border_showing)
    { border_showing_ = border_showing; return this; }

    public boolean
    bordered()
    { return border_showing_; }

    public void
    draw(Graphics graphics)
    {
        if (border_showing_) {
            this.draw_border(
                graphics,
                x_ - (w_ >> 1) - 1,
                y_ - (h_ >> 1) - 1,
                w_ + 2, h_ + 2
            );
        }
    }

    public Sprite
    draw_border(Graphics graphics, int x, int y, int w, int h)
    {
        graphics.setColor(Color.BLUE);
        graphics.drawRect(x, y, w, h);
        return this;
    }

    public boolean
    contains_point(int x, int y)
    {
        int half_w = w_ >> 1,
            half_h = h_ >> 1,
            left   = x_ - half_w,
            right  = x_ + half_w,
            top    = y_ - half_h,
            bottom = y_ + half_h;
        return (left <= x && x <= right) && (top <= y && y <= bottom);
    }

    public DataInputStream
    read_from_stream(InputStream is) throws IOException
    {
        var data = new DataInputStream(is);

        x_ = data.readInt();
        x_ = data.readInt();
        w_ = data.readInt();
        h_ = data.readInt();

        int red   = data.readInt();
        int green = data.readInt();
        int blue  = data.readInt();

        color_ = new Color(red, green, blue);
        return data;
    }

    public DataOutputStream
    write_to_stream(OutputStream os) throws IOException
    {
        var data = new DataOutputStream(os);
        data.writeInt(x_);
        data.writeInt(y_);
        data.writeInt(w_);
        data.writeInt(h_);
        data.writeInt(color_.getRed());
        data.writeInt(color_.getGreen());
        data.writeInt(color_.getBlue());
        return data;
    }
}
