package com.elias.mibocontrollapp.ui

import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.hilt.navigation.compose.hiltViewModel
import androidx.navigation.NavHostController
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import com.elias.mibocontrollapp.ui.screens.HomeScreen
import com.elias.mibocontrollapp.ui.screens.ManualControllScreen
import com.elias.mibocontrollapp.viewmodel.MiboViewmodel

object Routes {

    const val HOME = "home"
    const val MANUAL = "manual"

}
@Composable
fun MiboNavGraph(
    navController: NavHostController,
    modifier: Modifier = Modifier,
    viewmodel: MiboViewmodel = hiltViewModel()
) {
    val startDestination: String = Routes.HOME

    NavHost(
        navController = navController,
        startDestination = startDestination,
        modifier = modifier
    ) {
        composable(Routes.HOME) {
            HomeScreen()
        }
        composable(Routes.MANUAL) {
            ManualControllScreen()
        }
    }
}