package fr.gungun974.androidminiaudioglitchonwakeuptest

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import fr.gungun974.androidminiaudioglitchonwakeuptest.ui.theme.AndroidMiniaudioGlitchOnWakeUpTestTheme

class MyNativeLib {
    init {
        try {
            System.loadLibrary("test_player")

        } catch(e: Exception) {

            println("Error reading the file: ${e.message}")
        }
    }

    external fun init()
}


class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        val myLib = MyNativeLib()
        myLib.init()

        enableEdgeToEdge()
        setContent {
            AndroidMiniaudioGlitchOnWakeUpTestTheme {
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
    Text(
        text = "Play 220hz sound",
                        modifier = Modifier.padding(innerPadding)
    )
                }
            }
        }
    }
}

