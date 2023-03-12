package objects;

import java.awt.Color;
import java.awt.Image;
import java.awt.Graphics;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.URL;
import javax.imageio.ImageIO;

import util.Vector2i;

public class Img extends Sprite
{
    private int vx_, vy_;
    private Image source_;

    public
    Img(int x, int y, int w, int h, Color color, String url)
    {
        super(x, y, w, h, color);
        vx_ = 1;
        vy_ = 1;

        try {
            source_ = url == null
                ? ImageIO.read(new File("assets/band.png"))
                : ImageIO.read(new URL(url));
        } catch(IOException e) {
            System.out.println("oops: " + e.getMessage());
        }
    }

    @Override public void
    draw(Graphics graphics)
    {
        super.draw(graphics);
        graphics.drawImage(
            source_,
            x_ - (w_ >> 1),
            y_ - (h_ >> 1),
            w_, h_, null
        );
    }

    @Override public DataInputStream
    read_from_stream(InputStream is) throws IOException
    {
        var data_is      = super.read_from_stream(is);
        String image_url = data_is.readUTF();

        source_ = ImageIO.read(new URL(image_url));
        return data_is;
    }

    @Override public DataOutputStream
    write_to_stream(OutputStream os) throws IOException
    {
        var data_os = super.write_to_stream(os);
        data_os.writeUTF(source_.toString());
        return data_os;
    }

    @Override public Img
    move(Vector2i direction)
    {
        int half_w = w_ >> 1,
            half_h = h_ >> 1;

        if ((x_ <= half_w) || (direction.x() - half_w <= x_)) {
            vx_ *= -1;
        }

        if ((y_ <= half_h) || (direction.y() - half_h <= y_)) {
            vy_ *= -1;
        }

        x_ += vx_;
        y_ += vy_;
        return this;
    }
}
