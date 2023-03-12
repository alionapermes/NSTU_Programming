package components;

import java.awt.GridLayout;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JPanel;

public class ControllPanel extends JPanel
{
    private JButton
        add_btn_,
        rm_btn_,
        state_switch_btn_,
        freeze_all_btn_,
        liveup_all_btn_;

    public
    ControllPanel()
    {
        add_btn_          = new JButton("add");
        rm_btn_           = new JButton("remove");
        state_switch_btn_ = new JButton("freeze/alive");
        freeze_all_btn_   = new JButton("freeze all");
        liveup_all_btn_   = new JButton("liveup all");

        super.setLayout(new GridLayout(1, 5));
        super.add(add_btn_);
        super.add(rm_btn_);
        super.add(state_switch_btn_);
        super.add(freeze_all_btn_);
        super.add(liveup_all_btn_);
    }

    public ControllPanel
    add_btn_clicked(ActionListener listener)
    { add_btn_.addActionListener(listener); return this; }

    public ControllPanel
    rm_btn_clicked(ActionListener listener)
    { rm_btn_.addActionListener(listener); return this; }

    public ControllPanel
    state_switch_btn_clicked(ActionListener listener)
    { state_switch_btn_.addActionListener(listener); return this; }

    public ControllPanel
    freeze_all_btn_clicked(ActionListener listener)
    { freeze_all_btn_.addActionListener(listener); return this; }

    public ControllPanel
    liveup_all_btn_clicked(ActionListener listener)
    { liveup_all_btn_.addActionListener(listener); return this; }
}
