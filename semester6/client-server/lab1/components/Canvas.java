package components;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;
import java.util.function.Consumer;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import objects.Img;
import objects.Sprite;
import objects.Polygon;
import util.Vector2i;

public class Canvas extends JPanel
{
    public enum State
    {
        IDLE, ADDING, REMOVING, STATE_SWITCHING
    }

    private ArrayList<Sprite> sprites_;
    private ExecutorService executor_;
    private ScheduledExecutorService scheduled_executor_;
    private Random random_;
    private State state_;

    public
    Canvas()
    {
        sprites_            = new ArrayList<>();
        executor_           = Executors.newSingleThreadExecutor();
        scheduled_executor_ = Executors.newSingleThreadScheduledExecutor();
        random_             = new Random();

        this.init();
    }

    @Override protected void
    paintComponent(Graphics graphics)
    {
        super.paintComponent(graphics);
        sprites_.forEach(sprite -> sprite.draw(graphics));
    }

    private void
    init()
    {
        this.init_controll_panel()
            .schedule_task()
            .set_mouse_handler()
            .setBackground(Color.WHITE);
    }

    private Canvas
    init_controll_panel()
    {
        var controll_panel = new ControllPanel();
        super.add(controll_panel, BorderLayout.SOUTH);

        controll_panel
            .add_btn_clicked(e -> {
                state_ = State.ADDING;
                sprites_.forEach(sprite -> sprite.set_border_showing(false));
            })
            .rm_btn_clicked(e -> {
                state_ = State.REMOVING;
                sprites_.forEach(sprite -> sprite.set_border_showing(true));
            })
            .state_switch_btn_clicked(e -> {
                state_ = State.STATE_SWITCHING;
                sprites_.forEach(sprite -> sprite.set_border_showing(true));
            })
            .freeze_all_btn_clicked(e -> sprites_.forEach(Sprite::freeze))
            .liveup_all_btn_clicked(e -> sprites_.forEach(Sprite::liveup));

        return this;
    }

    private Canvas
    schedule_task()
    {
        final int
            start_time = 0,
            period     = 16;

        final Runnable task = () -> {
            executor_.submit(() -> sprites_.forEach(sprite -> {
                if (sprite.alive()) {
                    var direction = new Vector2i(
                        this.getWidth(), this.getHeight());
                    sprite.move(direction);
                }
            }));

            SwingUtilities.invokeLater(this::repaint);
        };

        scheduled_executor_.scheduleAtFixedRate(
            task, start_time, period, TimeUnit.MILLISECONDS);

        return this;
    }

    private Canvas
    set_mouse_handler()
    {
        this.addMouseListener(new MouseAdapter() {
            @Override public void
            mouseClicked(MouseEvent e) {
                int x = e.getX(),
                    y = e.getY();

                final Consumer<Sprite> state_switcher = sprite -> {
                    if (sprite.alive()) {
                        sprite.freeze();
                    } else {
                        sprite.liveup();
                    }
                };

                if (state_ == State.REMOVING) {
                    sprites_.removeIf(sprite -> sprite.contains_point(x, y));
                    return;
                }

                if (state_ == State.STATE_SWITCHING) {
                    sprites_.stream()
                        .filter(sprite -> sprite.contains_point(x, y))
                        .findFirst()
                        .ifPresent(state_switcher);
                    return;
                }

                int size = random_.nextInt(50, 300);
                if (e.getButton() == MouseEvent.BUTTON1) {
                    sprites_.add(new Img(x, y, size, size, null, null));
                } else if (e.getButton() == MouseEvent.BUTTON3) {
                    var faces = random_.nextInt(3, 16);
                    sprites_.add(
                        new Polygon(x, y, size, size, Color.BLACK, faces));
                }
            }
        });

        return this;
    }
}
