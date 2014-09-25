package apps.bubbleemup;

import android.os.Bundle;
import android.app.Activity;
import android.view.View;
import android.widget.ImageButton;
import android.view.Menu;
import android.view.MenuItem;
import android.support.v4.app.NavUtils;

public class MainActivity extends Activity {

    @Override
    public void onCreate(Bundle savedInstanceState) {
    	super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }
    
    public void go_puzzle_world(View view) {
    	setContentView(R.layout.puzzle_world);
    }
    
    public void go_puzzle_w1(View view) {
    	setContentView(R.layout.puzzle_levels);
    }
    
    public void go_puzzle_w2(View view) {
    	setContentView(R.layout.puzzle_levels);
    }
    
    public void go_puzzle_w3(View view) {
    	setContentView(R.layout.puzzle_levels);
    }
    
    public void go_arcade_levels(View view) {
    	setContentView(R.layout.arcade_levels);
    }
    
    public void go_game(View view) {
    	setContentView(R.layout.game);
    }
    
    public void go_main(View view) {
    	setContentView(R.layout.activity_main);
    }
    
    public void leave(View view) {
    	finish();
    }

    
}
