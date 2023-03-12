package objects;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.AffineTransform;

import util.Vector2i;

public class Star extends Sprite
{
    private int vertices_num_;
    private double angle_;

    public
    Star(int x, int y, int w, int h, Color color)
    {
        super(
            x - (w >> 1),
            y - (h >> 1),
            w, h, color
        );
    }

    public
    Star(int x, int y, int w, int h, Color color, int vertices_num)
    {
        super(x, y, w, h, color);
        vertices_num_ = vertices_num;
    }

    @Override public void
    draw(Graphics graphics)
    {
        if (this.bordered()) {
            this.draw_border(graphics, x_, y_, w_, h_);
        }

        var g2d = (Graphics2D)graphics;

        var original_transform = g2d.getTransform();
        var rotated_transform  = AffineTransform.getRotateInstance(
            angle_, x_ + (w_ >> 1), y_ + (h_ >> 1));

        g2d.transform(rotated_transform);
        draw_lines(graphics);
        g2d.setTransform(original_transform);
    }

    @Override public Star
    move(Vector2i direction)
    { angle_ += 0.1; return this; }

    private void
    draw_lines(Graphics graphics)
    {
        int mid_x = x_ + (w_ >> 1),
            mid_y = y_ + (h_ >> 1);

        double radius = w_ / 2.0;

        var vertices_x = new int[vertices_num_];
        var vertices_y = new int[vertices_num_];

        for (int cur = 0; cur < vertices_num_; cur++) {
            double
                rad = (cur << 1) * (Math.PI / vertices_num_),
                x   = mid_x + Math.cos(rad) * radius,
                y   = mid_y + Math.sin(rad) * radius;
            vertices_x[cur] = (int)x;
            vertices_y[cur] = (int)y;
        }

        graphics.setColor(color_);
        for (int i = 2; i < vertices_x.length; i++) {
            graphics.drawLine(
                vertices_x[i],
                vertices_y[i],
                vertices_x[i - 2],
                vertices_y[i - 2]
            );
        }

        graphics.drawLine(
            vertices_x[vertices_x.length - 1],
            vertices_y[vertices_y.length - 1],
            vertices_x[1], vertices_y[1]
        );
        graphics.drawLine(
            vertices_x[vertices_x.length - 2],
            vertices_y[vertices_y.length - 2],
            vertices_x[0], vertices_y[0]
        );
    }
}
