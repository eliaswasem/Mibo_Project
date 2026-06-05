package com.elias.mibocontrollapp

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Icon
import androidx.compose.material3.NavigationBar
import androidx.compose.material3.NavigationBarItem
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.getValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.navigation.compose.currentBackStackEntryAsState
import androidx.navigation.compose.rememberNavController
import com.elias.mibocontrollapp.ui.MiboNavGraph
import com.elias.mibocontrollapp.ui.Routes
import com.elias.mibocontrollapp.ui.theme.MiboControllAppTheme
import dagger.hilt.android.AndroidEntryPoint
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.*


@AndroidEntryPoint
class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            MiboControllAppTheme {
                val navController = rememberNavController()
                val navBackStackEntry by navController.currentBackStackEntryAsState()
                val currentRoute = navBackStackEntry?.destination?.route

                Scaffold(
                    modifier = Modifier.fillMaxSize(),
                    bottomBar = {
                        NavigationBar {
                            NavigationBarItem(
                                selected = currentRoute == Routes.HOME,
                                onClick = {
                                    if (currentRoute != Routes.HOME) {
                                        navController.navigate(Routes.HOME) {
                                            launchSingleTop = true
                                            restoreState = true
                                        }
                                    }
                                },
                                icon = { Icon(Icons.Default.Home, contentDescription = "Home") },
                                label = { Text(stringResource(R.string.label_home)) }
                            )
                            /*
                            NavigationBarItem(
                                selected = currentRoute == Routes.DAY,
                                onClick = {
                                    if (currentRoute != Routes.DAY) {
                                        navController.navigate(Routes.DAY) {
                                            launchSingleTop = true
                                            restoreState = true
                                        }
                                    }
                                },
                                icon = { Icon(Icons.Default.Cloud, contentDescription = "Day") },
                                label = { Text(stringResource(R.string.label_day)) }
                            )
                            NavigationBarItem(
                                selected = currentRoute == Routes.WEEK,
                                onClick = {
                                    if (currentRoute != Routes.WEEK) {
                                        navController.navigate(Routes.WEEK) {
                                            launchSingleTop = true
                                            restoreState = true
                                        }
                                    }
                                },
                                icon = { Icon(Icons.Default.Cloud, contentDescription = "Week") },
                                label = { Text(stringResource(R.string.label_week)) }
                            )
                            NavigationBarItem(
                                selected = currentRoute == Routes.SETTINGS,
                                onClick = {
                                    if (currentRoute != Routes.SETTINGS) {
                                        navController.navigate(Routes.SETTINGS) {
                                            launchSingleTop = true
                                        }
                                    }
                                },
                                icon = {
                                    Icon(
                                        Icons.Default.Settings,
                                        contentDescription = "Settings"
                                    )
                                },
                                label = { Text(stringResource(R.string.label_settings)) }
                            )

                             */

                        }

                    }

                    ) { innerPadding ->
                    MiboNavGraph(
                        navController = navController,
                        modifier = Modifier.padding(innerPadding),
                    )

                }
            }
        }
    }
}
