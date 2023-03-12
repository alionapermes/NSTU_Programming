import javax.swing.*;

import components.Canvas;

public class Main {
    public static void main(String[] args) {
        var window = new JFrame("Lab 1");

        window.setContentPane(new Canvas());
        window.setSize(800, 600);
        window.setVisible(true);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}
